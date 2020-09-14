#pragma once
#include <iostream>

// Common interface for all the devices the remote will control
class Device
{
public:
	virtual void turnOn() = 0;
	virtual void turnOff() = 0;
	virtual void plus() = 0;
	virtual void minus() = 0;
};

// Common interface for all the command classes
class ICommand
{
public:
	virtual void execute() = 0;
};

// Each command supported by the remote must be an object itself, that means it must have a well defined class.
// Each command class has the responsibility to accept a command/method and correctly call the method of the receiver 
// class. Here, for the remote, the receiver classes are TV and AC as the command you give through the remote is actually
// received and served by these devices.
// Since this is a template class, so for each command a new class will get created as intended

template <typename T>
class Executor : public ICommand
{
	void(T::*method)(); // A placeholder function pointer
public:
	Executor(void(T::*meth)() = 0)
		:ICommand()
	{
		method = meth;
	}
	virtual void execute() override
	{
		((new T())->*method)();
	}
};

// Receiver class for the command objects
class TV : public Device
{
public:
	TV() = default;
	virtual void turnOn() override
	{
		std::cout << "Turning On TV!" << std::endl;
	}
	virtual void turnOff() override
	{
		std::cout << "Turning OFF TV!" << std::endl;
	}
	virtual void plus() override
	{
		std::cout << "Increasing channel On TV!" << std::endl;
	}
	virtual void minus() override
	{
		std::cout << "Decreasing channel On TV!" << std::endl;
	}
};

// Receiver class for the command objects
class AC : public Device
{
public:
	virtual void turnOn() override
	{
		std::cout << "Turning On AC!" << std::endl;
	}
	virtual void turnOff() override
	{
		std::cout << "Turning OFF AC!" << std::endl;
	}
	virtual void plus() override
	{
		std::cout << "Increasing temperature On AC!" << std::endl;
	}
	virtual void minus() override
	{
		std::cout << "Decreasing temperature On AC!" << std::endl;
	}

};

// This class is the invoker class. That means, its job is to invoke the commands.
// The commands are routed correctly by the corresponding class of each command to the receiver class.
class Remote
{
public:
	Remote(){}
	template <typename T>
	void pressButton(void(T::* command)())
	{
		Executor<T>* executor = new Executor<T>(command);
		executor->execute();
	}
};


