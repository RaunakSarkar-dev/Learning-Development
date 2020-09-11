#include <iostream>
#include "WorkerThread_Impl.hpp"

void func1()
{
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "In Func1 that runs Asynchronously " << std::endl;
}

void func2()
{
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "In Func2 that runs Synchronously " << std::endl;
}

static constexpr bool ASYNC = false;
static constexpr bool SYNC = true;

int main()
{
    Worker worker;
    worker.start();
    worker.delegateTask(ASYNC, &func1);
    int counter = 0;
    while (counter++<20)
    {
        std::cout << "Yo " << std::endl;        
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if(counter == 4) // Just to illustrate the synchronous thread working a bit better in the console
            worker.delegateTask(SYNC, &func2);
    }   
    worker.join();
}
