#pragma once

#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <algorithm>

#include "Types.hpp"
#include "Server.hpp"

class MessageManager
{
private:
	std::queue<Message> messageQueue; // The queue that holds the messages
	int messageCounter; // To keep the count of messages and generate MessageID for each message

public:
	MessageManager()
		: messageQueue()
		, messageCounter(0)
	{
	}

	~MessageManager()
	{
	}

	bool enqueue(Message data)
	{
		if (messageQueue.size() == SIZE - 1)
			return false;
		messageQueue.emplace(data); // Enters the data in form of a message in the queue
		messageCounter++;
		return true;
	}

	Message dequeue()
	{
		Message temp;
		if (messageQueue.size() == 0)
		{
			temp.first = -1;
			temp.second = "Underflow";
		}
		else
		{
			temp = messageQueue.front();
			messageQueue.pop();
			messageCounter--;
		}
		return temp; // Return the data of the deleted message
	}

	Message constructMessage(std::string data)
	{
		return std::make_pair(messageCounter++, data); // Create a message from the provided data to put in the queue
	}

	int getMessageId()
	{
		return messageCounter;
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


class RequestBroker
{
public:
	RequestBroker()
		: mThread(nullptr)
		, messageList()
		, listeners()
		, msgId(0)
	{
	}
	~RequestBroker()
	{
	}

	bool createThread()
	{
		if (!mThread)
			mThread = new std::thread(&RequestBroker::pollQueue, this);
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

	void pollQueue()
	{
		while (1) // Busy-waiting
		{
			std::unique_lock<std::mutex> lock(mutex); // Gaurd against multi thread access
			while (messageList.isEmpty())
			{
				std::cout << "POLL REQUEST" << std::endl;
				cv.wait(lock);
			}
			if (!messageList.isEmpty())
			{
				std::cout << " POLL REQ" << std::endl;
				std::for_each(listeners.begin(), listeners.end(), [this](Component* x) {
					Message msg = messageList.dequeue();
 					x->receiveRequest(msg);
				});
					
			}
			lock.unlock();
		}
	}

	void addListener(Component* comp)
	{
		listeners.push_back(comp);
	}

	int submitRequest(const std::string& homework)
	{
		std::unique_lock<std::mutex> lock(mutex);
		std::cout << "SUBMIT REQUEST" << std::endl;
		Message msg;
		msg.first = messageList.getMessageId();
		msg.second = homework;
		msgId = msg.first;
		messageList.enqueue(msg);
		lock.unlock();
		cv.notify_all();// Notify the PollClass after each successful submission
		return msgId;
	}


	void submitResponse(const std::string& homework)
	{
		std::cout << "SUBMIT RESPONSE" << std::endl;
		std::unique_lock<std::mutex> lock(mutex);
		Message msg;
		msg.first = msgId;
		msg.second = homework;
		messageList.enqueue(msg);
		lock.unlock();
		cv.notify_all(); // Notify the PollClass after each successful submission
	}

	int getMessageId()
	{
		return msgId;
	}
	
private:
	std::thread* mThread;
	MessageManager messageList;
	std::mutex mutex;
	std::condition_variable cv;
	std::vector<Component*> listeners;
	int msgId;
};
