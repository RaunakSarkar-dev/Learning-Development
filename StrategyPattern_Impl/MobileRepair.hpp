#pragma once

#include "CommonTypes.hpp"

namespace Mobile
{
	// This could be handled better using enum class and "using" declarative in c++20
	static constexpr int SCREEN = 1;
	static constexpr int CHARGING_PORT = 2;

	class MobileRepair : public Mechanic
	{
	public:
		/* Implement this function in the derived classes with each class having its own algorithm for repairing*/
		virtual void repair() = 0;
	};

	class ScreenRepair : public MobileRepair
	{
	public:

		void repair() override
		{
			/* Insert the Algorithm here.*/
			std::cout << "Mobile: I am repairing the Screen!" << std::endl;
		}
	};

	class ChargingPortRepair : public MobileRepair
	{
	public:

		void repair() override
		{
			/* Insert the Algorithm here.*/
			std::cout << "Mobile: I am repairing the Charging point!" << std::endl;
		}
	};
}
