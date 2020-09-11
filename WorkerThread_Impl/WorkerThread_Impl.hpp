#pragma once

// Following is just a conceptual implementation of a Worker thread.

#include <queue>
#include <iostream>
#include <functional>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>

// Parent thread class that takes care of all Generic thread operations
class Thread
{
	std::thread* mThread = nullptr;
public:
	// Creates a new thread
	bool createThread()
	{
		if (!mThread)
			mThread = new std::thread(&Thread::run, this);
		return true;
	}

	// Joins the current thread with the thread it is called from
	void join()
	{
		if (!mThread)
			return;

		mThread->join();
		delete mThread;
		mThread = nullptr;
	}

	// Detaches the current thread with the thread it is called from. It is an irreversible operation
	void detach()
	{
		if (mThread)
			mThread->detach();
	}

	virtual ~Thread()
	{
		join();
	}

protected:
	virtual void run() = 0; // This needs to be implemented in the derived class as per requirement
};

// Make worker a thread class
class Worker : public Thread
{
	std::mutex mutex;
	std::condition_variable cv;
	std::queue<std::function<void()>> tasks;
	std::atomic<bool> isRunning;
public:
	Worker() : tasks(), isRunning(false)
	{
		createThread();
	}

	// This class is capable of scheduling tasks both synchronous and asynchronously
	void delegateTask(bool inSync, const std::function<void()>& func)
	{
		if(!inSync)
		{
			std::cout << "Task scheduled Asynchronously" << std::endl;
			std::unique_lock<std::mutex> l(mutex);
			tasks.push(func);
			l.unlock();
			cv.notify_all();
		}
		else
		{
			std::cout << "Task scheduled Synchronously" << std::endl;
			std::atomic<bool> finished = false;
			std::unique_lock<std::mutex> l(mutex);
			tasks.push([&func, &finished]{
				func();
				finished = true;
			});
			cv.notify_all();
			// Block the thread till the execution of the scheduled task is complete
			while (!finished)
				cv.wait(l);
		}
		
	}

	// Start the thread operations
	void start()
	{
		isRunning = true;
	}

	// Stop the thread operations
	void stop()
	{
		isRunning = false;
	}

	// Core implementation of the work that is expected out of this worker class
	void run() override
	{
		std::unique_lock<std::mutex> lock(mutex);
		do
		{
			while (isRunning && tasks.empty())
				cv.wait(lock);

			while (!tasks.empty())
			{
				auto function = tasks.front();
				tasks.pop();
				lock.unlock();
				function();
				lock.lock();
			}
			cv.notify_all();
		} while (isRunning);
		cv.notify_all();
	}
};
