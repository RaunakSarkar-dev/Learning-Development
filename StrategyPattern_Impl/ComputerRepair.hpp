#pragma once
#include "CommonTypes.hpp"

namespace Computer
{ 
	// This could be handled better using enum class and "using" declarative in c++20
	static constexpr int MONITOR = 1;
	static constexpr int HDD = 2;
	static constexpr int MOTHERBOARD = 3;
	
	class ComputerRepair : public Mechanic
	{
	public:
		/* Implement this function in the derived classes with each class having its own algorithm for repairing*/
		virtual void repair() = 0;
	};


	// Eg: This class specializes in the motherboard repairing and only has the algorith to repair motherboard
	// that must be implemented inside the repair function
	class MotherBoardRepair : public ComputerRepair
	{
	public:

		void repair() override
		{
			/* Insert the Algorithm here.*/
			std::cout << "Computer: I am repairing the motherboad!" << std::endl;
		}
	};

	class HardDriveRepair : public ComputerRepair
	{
	public:

		void repair() override
		{
			/* Insert the Algorithm here.*/
			std::cout << "Computer: I am repairing the HardDrive!" << std::endl;
		}
	};

	class MonitorRepair : public ComputerRepair
	{
	public:

		void repair() override
		{
			/* Insert the Algorithm here.*/
			std::cout << "Computer: I am repairing the Monitor!" << std::endl;
		}
	};
}
