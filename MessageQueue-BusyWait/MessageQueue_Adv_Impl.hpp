#pragma once

#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <memory>

typedef std::pair<int,std::string> Message;
static constexpr int SIZE = 8;

// This is a class representation of a Message Queue
// The message queue implemented here is a singleton instance so that all objects share the same queue 
class MessageManager
{
private:
	std::queue<Message> messageQueue; // The queue that holds the messages
	int messageCounter; // To keep the count of messages and generate MessageID for each message
	MessageManager()
		: messageQueue()
		, messageCounter(0)
	{
	}
	static MessageManager* instance; // To access the singleton instance since the constructor is private
public:

	MessageManager(MessageManager&) = delete;
	MessageManager(MessageManager&&) = delete;
	MessageManager operator =(MessageManager&) = delete; // Deleted all other accessors to maintain only one instance

	~MessageManager()
	{
		delete instance;
		instance = 0;
	}

	static MessageManager* getInstance()
	{
		if (instance == nullptr)
			instance = new MessageManager(); // Returns a new instance when no instance has been created
		return instance; // All other cases, the already created instance is returned
	}

	bool enqueue(std::string data)
	{		 
		if (messageQueue.size() == SIZE-1)
			return false;
		messageQueue.emplace(constructMessage(data)); // Enters the data in form of a message in the queue
		return true;
	}

	std::string dequeue() 
	{
		if (messageQueue.size() == 0)
			return "Underflow";
		else
		{
			std::this_thread::sleep_for(std::chrono::seconds(10));
			Message temp = messageQueue.front();
			messageQueue.pop();
			messageCounter--;
			return temp.second; // Return the data of the deleted message
		}
	}

	Message constructMessage(std::string data)
	{
		return std::make_pair(messageCounter++, data); // Create a message from the provided data to put in the queue
	}

	bool isEmpty()
	{
		return messageQueue.empty();
	}

	void showMessage()
	{
		std::cout << "There are currently: " << messageCounter << " messages in the queue. They are: " << std::endl;
	}
};

class Teacher
{
public:
	Teacher()
	{
	}
	// Teacher reads the data from the message queue
	void receiveHomework(std::string homework)
	{
		std::cout << homework << std::endl;
	}
};


// Responsible for receiving homework from Students and submiting them to teacher for checking
class ClassMonitor
{
public:
	ClassMonitor()
		: mThread(nullptr)
	{
		teacherDesk = MessageManager::getInstance();
		classTeacher = new Teacher();
	}
	~ClassMonitor() 
	{
		delete teacherDesk;
		teacherDesk = 0;
	}

	bool createThread()
	{
		if (!mThread)
			mThread = new std::thread(&ClassMonitor::pollClass, this);
		return true;
	}

	void exitThread()
	{
		mThread->join();
		delete mThread;
		mThread = 0;
	}

	std::thread::id getThreadContext()
	{
		return mThread->get_id();
	}

	void pollClass()
	{
		while(1) // Busy-waiting
		{
			std::unique_lock<std::mutex> lock(mutex); // Gaurd against multi thread access
			while (teacherDesk->isEmpty())
				cv.wait(lock);
			if (!teacherDesk->isEmpty())
			{	
				teacherDesk->showMessage();
				classTeacher->receiveHomework(teacherDesk->dequeue());
			}
		}
	}

	void submitHomework(std::string homework)
	{
		std::unique_lock<std::mutex> lock(mutex);
		teacherDesk->enqueue(homework);
		std::cout << "SUBMIT" << std::endl;
		lock.unlock();
		cv.notify_one(); // Notify the PollClass after each successful submission
	}

private:
	std::thread* mThread;
	MessageManager* teacherDesk;
	Teacher* classTeacher;
	std::mutex mutex;
	std::condition_variable cv;
};

class Student1
{
	ClassMonitor* monitor;
public:
	Student1(ClassMonitor* monitor)
		:monitor(monitor)
	{}
	// Student1 puts the data into the message queue
	void submitHomework()
	{
		monitor->submitHomework("Student1: Complete");
	}

};

class Student2
{
	ClassMonitor* monitor;
public:
	Student2(ClassMonitor* monitor)
		:monitor(monitor)
	{}
	// Student2 puts the data into the message queue
	void submitHomework()
	{
		monitor->submitHomework("Student2: Complete");
	}
};
