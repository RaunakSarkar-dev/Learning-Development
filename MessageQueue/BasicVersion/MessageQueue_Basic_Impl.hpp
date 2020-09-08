#pragma once

#include <iostream>
#include <queue>
#include <string>

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
			Message temp = messageQueue.front();
			messageQueue.pop();
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

	void showMessage(std::queue<Message> q)
	{
		std::cout << "There are currently: " << messageCounter << " messages in the queue. They are: " << std::endl;
		while (!q.empty())
		{
			std::cout << q.front().second << " ";
			q.pop();
		}
		std::cout << std::endl;
	}
};

MessageManager* MessageManager::instance = nullptr; // Need to initialize static variables outside the class

class Teacher
{
	MessageManager* teacherDesk;
public:
	Teacher()
	{
		teacherDesk = MessageManager::getInstance();
	}
	// Teacher reads the data from the message queue
	void receiveHomework()
	{
		while (!teacherDesk->isEmpty())
		{
			std::cout << teacherDesk->dequeue() << std::endl;
		}
	}
};

class Student1
{
	MessageManager* teacherDesk;
public:
	Student1()
	{
		teacherDesk = MessageManager::getInstance();
	}
	// Student1 puts the data into the message queue
	void submitHomework()
	{
		if (teacherDesk->enqueue("Student1: Complete"))
			std::cout << "Student1: Successfully submitted my Homework" << std::endl;
		else
			std::cout << "Student1: Failed to submit my Homework. No space in teacher's desk";
	}

};

class Student2
{
	MessageManager* teacherDesk;
public:
	Student2()
	{
		teacherDesk = MessageManager::getInstance();
	}
	// Student2 puts the data into the message queue
	void submitHomework()
	{
		if (teacherDesk->enqueue("Student2: Complete"))
			std::cout << "Student2: Successfully submitted my Homework" << std::endl;
		else
			std::cout << "Student2: Failed to submit my Homework. No space in teacher's desk";
	}
};
