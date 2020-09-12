#pragma once

#include<iostream>


enum class DeviceType
{
	COMPUTER,
	MOBILE
};

// An abstract class that is derived and implemented by different classes which harbours their own algorithm
// for repairing damaged computer parts

class Mechanic
{
public:
	/* Implement this function in the derived classes with each class having its own algorithm for repairing*/
	virtual void repair() = 0;
};
