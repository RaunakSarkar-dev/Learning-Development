#pragma once
#include <iostream>

static constexpr int SIZE = 8;
static constexpr int INVALID = -65535;

// Collection of all implemented States
enum {
	UNDEFINED = -1,
	INITIAL,
	SUM,
	DIFF,
	MUL,
	DIV,
	WAIT,
	OUTPUT,
	ERROR
};

// Interface for all supported actions on States
class IActionHandler
{
public:
	IActionHandler() = default;
	virtual ~IActionHandler(){}
	virtual void sum() = 0;
	virtual void difference() = 0;
	virtual void multiply() = 0;
	virtual void div() = 0;
	virtual void input() = 0;
	virtual void error() = 0;
	virtual void check() = 0;
	virtual void defaultAction() = 0;
};


// Finite State Machine
class FSM
{
public:
	FSM(IActionHandler& actHandle)
		: currentState(UNDEFINED)
		, decision(-1)
		, actionHandler(actHandle)
	{
	}
	void init()
	{
		if (currentState == UNDEFINED)
		{
			enterState(INITIAL);
		}
	}

	void transition(const int& startState, const int& endState)
	{
		if (startState != endState)
		{
			leaveState(startState);
			enterState(endState);
		}
	}

	void transition(const int& startState)
	{
		if (startState == WAIT)
		{
			leaveState(startState);
			switch (decision)
			{
				case 1: enterState(SUM); break;
				case 2: enterState(DIFF); break;
				case 3: enterState(MUL); break;
				case 4: enterState(DIV); break;
				default: std::cout << " Wrong decision." << std::endl; enterState(ERROR); break;
			}
			decision = -1;
		}
	}

	void success()
	{
		if (currentState == INITIAL)
		{
			transition(INITIAL,WAIT);
		}
		if (currentState == WAIT)
		{
			transition(WAIT);
		}
		if (currentState == SUM)
		{
			transition(SUM, OUTPUT);
		}
		if (currentState == DIFF)
		{
			transition(DIFF, OUTPUT);
		}
		if (currentState == MUL)
		{
			transition(MUL, OUTPUT);
		}
		if (currentState == DIV)
		{
			transition(DIV, OUTPUT);
		}
		if (currentState == OUTPUT)
		{
			transition(OUTPUT, WAIT);
		}
		if (currentState == ERROR)
		{
			std::cout << "ERROR" << std::endl;
			exit(0);
		}
	}

	void failure()
	{
		if (currentState == INITIAL)
		{
			transition(INITIAL, ERROR);
		}
		if (currentState == WAIT)
		{
			transition(WAIT, ERROR);
		}
		if (currentState == SUM)
		{
			transition(SUM, ERROR);
		}
		if (currentState == DIFF)
		{
			transition(DIFF, ERROR);
		}
		if (currentState == MUL)
		{
			transition(MUL, ERROR);
		}
		if (currentState == DIV)
		{
			transition(DIV, ERROR);
		}
		if (currentState == OUTPUT)
		{
			transition(OUTPUT, ERROR);
		}
	}

	void enterState(const int state)
	{
		currentState = state;
		switch (state)
		{
			case INITIAL: actionHandler.defaultAction(); break;
			case SUM: actionHandler.sum(); break;
			case DIFF: actionHandler.difference(); break;
			case MUL: actionHandler.multiply(); break;
			case DIV: actionHandler.div(); break;
			case WAIT: actionHandler.input(); break;
			case OUTPUT: actionHandler.check(); break;
			case ERROR: actionHandler.error(); break;	
			case UNDEFINED: std::cout << "Undefined state" << std::endl;break;
			default: break;
		}
	}

	void leaveState(const int state)
	{
		switch (state)
		{
			case INITIAL: std::cout << "State Machine Exited" << std::endl; currentState = ERROR; break;
			case UNDEFINED: std::cout << "Undefined state" << std::endl; break;
		}
	}

	void setDecision(const int& dec)
	{
		decision = dec;
	}

private:
	IActionHandler& actionHandler;

	int currentState;
	int decision;
};

// Driver class to implement and start the State Machine
class SparkPlug : public IActionHandler
{
private:
	FSM stateMachine;
	int value;
public:
	SparkPlug()
		: stateMachine(*this)
		, value(INVALID)
	{
	}
	virtual ~SparkPlug() {}
	virtual void sum()
	{
		int a, b;
		std::cout << " Enter 2 numbers: " << std::endl;
		std::cin >> a >> b;
		if (a > 0 && b > 0)
		{
			value = a + b;
			stateMachine.success();
		}
		else
			stateMachine.failure();

	}
	virtual void difference()
	{
		int a, b;
		std::cout << " Enter 2 numbers: " << std::endl;
		std::cin >> a >> b;
		if (a > 0 && b > 0 && a > b) 
		{
			value = a - b;
			stateMachine.success();
		}
		else
			stateMachine.failure();
	}
	virtual void multiply()
	{
		int a, b;
		std::cout << " Enter 2 numbers: " << std::endl;
		std::cin >> a >> b;
		if (a > 0 && b > 0)
		{
			value = a * b;
			stateMachine.success();
		}
		else
			stateMachine.failure();
	}
	virtual void div()
	{
		int a, b;
		std::cout << " Enter 2 numbers: " << std::endl;
		std::cin >> a >> b;
		if (b > 0)
		{
			value = a / b;
			stateMachine.success();
		}
		else
			stateMachine.failure();
	}
	virtual void input()
	{
		int decision;
		std::cout << " Enter your option: " << std::endl;
		std::cout << " 1. Sum " << std::endl;
		std::cout << " 2. Diff " << std::endl;
		std::cout << " 3. Mul " << std::endl;
		std::cout << " 4. Div " << std::endl;
		std::cout << " 5. Quit " << std::endl;
		std::cin >> decision;
		if (decision == 5)
			stateMachine.failure();
		else
		{
			stateMachine.setDecision(decision);
			stateMachine.success();
		}
	}

	virtual void error() 
	{
		value = INVALID;
		stateMachine.success();	
	}
	virtual void check() 
	{
		std::cout << " Output: " << value << std::endl;
		stateMachine.success();
	}
	virtual void defaultAction()
	{
		stateMachine.success();
	}
	void spark()
	{
		stateMachine.init();
	}
};
