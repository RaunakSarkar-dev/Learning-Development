// Author: Raunak Sarkar

/* PROBLEM: Write a program that spawns two threads, one thread writes the values from 1 to input(user input) 
*           and the other thread writes the values from input to 1 in the same output file.
*  INPUTS:  A non-negative int value upto which the threads will compute the value and the outpur file where the values will be written
*  EXAMPLE: N = 10, Output = "Output.txt"
*           >> cat "Output.txt"
*           >> 1
*           >> 10
*           >> 2
*           >> 9
*           >> 3
*           >> 8
*              ...
*/


#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <thread>
#include <condition_variable> // The semaphore mechanism used for thread synchronization

// Should always avoid global variables.
// This should be put in a class structure, avoided to decrease complexity here. 
std::condition_variable cv;
std::mutex mutex,fmutex;
bool isFinished = false;
constexpr auto _FILE = "Output.txt";

// This class is responsible for all tehe logic and management related to opening and writing to a file or console
class Logger
{
   std::string fileName;
   int fileMode;
public:
   void configureFile(std::string const& name, int const& mode)
   {
      fileName = name;
      fileMode = mode;
   }
   void writeToFile(std::string const& msg)
   {
      // The file is a resource shared between two threads, so it should be put under mutex lock
      std::unique_lock<std::mutex> l(fmutex);
      std::ofstream outFile;
      outFile.open(fileName, fileMode);
      outFile << msg << "\n";
      outFile.close();
   }

   void writeToConsole(std::string const& msg)
   {
      // The console is also a resource shared between two threads, so it should be put under mutex lock
      std::unique_lock<std::mutex> l(fmutex);
      std::cout << msg << std::endl;
   }

   bool isExist(std::string const& file)
   {
      // Check if the file exists
      return std::ifstream(file).good();
   }
};

// NOTE: writeBackwards and writeForwards are waiting on each other's operation here. This is a classic case 
//       which has very high potential for a deadlock. Be very careful during handling!
void writeBackwards(int const& upperLimit, Logger* log)
{
   for (int i = upperLimit; i > 0;)
   {
      // Block the thread on the condition that isFinished is true. So when isFinished is set to true, this thread will resume
      // isFinished is set true in writeForwards class and thus writeBackwards waits till writeForwards have written its value
      // and hence synchronization is acheived.
      std::unique_lock<std::mutex> l(mutex);
      cv.wait(l, []() {return isFinished; });
      log->writeToFile(std::to_string(i--));
      //log->writeToConsole(std::to_string(i--));
      isFinished = false;
      l.unlock(); // Always unlock the mutex once the critical section is over
      cv.notify_all(); // Notify all the waiting threads that the critical section exection has finished.
   }
}

void writeForwards(int const& upperLimit, Logger* log)
{
   for (int i = 1; i <= upperLimit;)
   {
      // Block the thread on the condition that isFinished is false. So when isFinished is set to flase, this thread will resume
      // isFinished is set true in writeForwards class and thus writeForward inturn waits till writeBackwards have written its value
      // and hence synchronization is acheived.
      std::unique_lock<std::mutex> l(mutex);
      cv.wait(l, []() {return !isFinished; });
      log->writeToFile(std::to_string(i++));
      //log->writeToConsole(std::to_string(i++));
      isFinished = true;
      l.unlock();
      cv.notify_all();
   }
}

int main()
{
   bool isFinished = false;
   Logger* logger = new Logger();
   if (logger->isExist(_FILE))
      remove(_FILE);
   logger->configureFile(_FILE, std::ios::app);

   std::thread t1(writeBackwards,10,logger);
   std::thread t2(writeForwards,10,logger);

   t1.join(); // The main thread will wait till execution of T1 is complete and then terminate itself
   t2.join(); // The main thread will wait till execution of T2 is complete and then terminate itself
}