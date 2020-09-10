#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <thread>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>

enum State {
	ALIVE,
	COMA,
	DEAD
};

std::string stateString(State s)
{
	switch (s)
	{
	case ALIVE: return std::string("Alive");
	case COMA: return std::string("COMA");
	case DEAD: return std::string("DEAD");
	}
}

class Patient {
public:

	std::atomic<State> condition;
	Patient()
		: condition(State::ALIVE)
	{}

	bool isAlive()
	{
		return (State::ALIVE == condition);
	}
	void die()
	{
		condition = State::DEAD;
	}

	bool isInComa()
	{
		return (condition == State::COMA);
	}
	void goToComa()
	{
		condition = State::COMA;
		std::cout << "The patient " << name() << " is in COMA " << std::endl;
	}

	void returnFromComa()
	{
		condition = State::ALIVE;
	}

	State getCondition()
	{
		return condition;
	}

	virtual std::string name() = 0;
	virtual void revive() = 0;
};


class Ventilation
{
public:
	void revivePatient(Patient* p)
	{
		p->revive();
		std::cout << "The patient " << p->name() << " is being revived." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
};


class Thread
{
	std::thread* mThread = nullptr;
public:

	bool createThread()
	{
		if (!mThread)
			mThread = new std::thread(&Thread::run,this);
		return true;
	}

	void join()
	{
		if (!mThread)
			return;

		mThread->join();
		delete mThread;
		mThread = nullptr;
	}

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
	virtual void run() = 0;
};

class HealthService : public Thread
{
	std::vector<Patient*> patients;
	Ventilation* vent;
	std::atomic<bool> isRunning;
	std::condition_variable stop_condition;
	std::mutex mutex;

public:
	HealthService() : patients() , isRunning(false)
	{
		vent = new Ventilation();
		createThread();		
	}

	void start()
	{
		isRunning = true;
	}

	void stop()
	{
		// Stopping condition
	}

	~HealthService()
	{
	}

	void registerPatients(Patient* pat)
	{
		patients.push_back(pat);
	}

	void checkHeartBeat()
	{
		std::for_each(patients.begin(), patients.end(), [&](Patient* it) {
			if (!it->isAlive())
			{
				checkVentilator(it);
			}
		});
		
	}

	virtual void run() override
	{
		if (!isRunning)
			return;

		while (isRunning)
		{
			showPatient();
			checkHeartBeat();
			std::this_thread::sleep_for(std::chrono::seconds(4));
		}
	}

	void checkVentilator(Patient* p)
	{
		vent->revivePatient(p);
	}

	void showPatient()
	{
		for (auto& x : patients)
			std::cout<< "The patient:  "<< x->name()<< " is " << stateString(x->getCondition()) << std::endl;
	}
};

class Patient1: public Patient, public Thread
{
	HealthService& health;
	std::atomic<bool> isRunning;
public:
	Patient1(HealthService& hs) : health(hs), isRunning(false)
	{
		createThread();
	}
	~Patient1()
	{
		join();
	}
	std::string name() override
	{
		return std::string("Patient1");
	}

	void registerPatient()
	{
		health.registerPatients(this);
		isRunning = true;
	}
	void revive() override
	{
		returnFromComa();
	}
	void run() override
	{
		if (!isRunning)
			return;
		while(isRunning)
		{
			goToComa();
			std::this_thread::sleep_for(std::chrono::seconds(10));
		}
	}

};

class Patient2 : public Patient, public Thread
{
	HealthService& health;
	std::atomic<bool> isRunning;
public:
	Patient2(HealthService& hs) : health(hs)
	{
		createThread();
	}
	void registerPatient()
	{
		health.registerPatients(this);
		isRunning = true;
	}
	void revive() override
	{
		returnFromComa();
	}

	~Patient2()
	{
		join();
	}

	void run() override
	{
		if (!isRunning)
			return;
		while (isRunning)
		{
			std::this_thread::sleep_for(std::chrono::seconds(15));
			goToComa();
		}
	}

	std::string name() override
	{
		return std::string("Patient2");
	}
};

