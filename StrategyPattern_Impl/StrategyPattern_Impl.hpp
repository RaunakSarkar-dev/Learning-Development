#pragma once

#include "ComputerRepair.hpp"
#include "MobileRepair.hpp"
#include "CommonTypes.hpp"

// The main class that receives the repair request and delegates it to ComputerRepair class to repair the damaged part
// This class strategically chooses the Repair Algorithm based on the nature of the damaged class
// Thus the algorithm is decoupled from the client/user of the algorithm
// So if you have to add an algorithm, just extend and implement Mechanic::repair method,
// RepairBusiness class wont be affected for that. It will only have to call the new algorithm as required

class RepairBusiness
{
public:
	RepairBusiness()
		: mechanic(nullptr)
	{
	}

	void damaged(DeviceType device, int parts)
	{
		switch (device) // Strategy: Decide which mechanic to call based on the damaged device type
		{
			case DeviceType::COMPUTER:
				repairComputer(parts);
				break;
			case DeviceType::MOBILE:
				repairMobile(parts);
				break;
			default:
				break;
		}
		mechanic->repair();
	}

	void repairComputer(int part)
	{
		delete mechanic;
		switch (part) // Strategy: Decide which repair algorithm to call based on the damaged device part
		{
			case Computer::MONITOR:
				mechanic = new Computer::MonitorRepair();
				break;
			case Computer::HDD:
				mechanic = new Computer::HardDriveRepair();
				break;
			case Computer::MOTHERBOARD:
				mechanic = new Computer::MotherBoardRepair();
				break;
			default:
				break;
		}
	}

	void repairMobile(int part)
	{
		delete mechanic;
		switch (part) // Strategy: Decide which repair algorithm to call based on the damaged device part
		{
		case Mobile::SCREEN:
			mechanic = new Mobile::ScreenRepair();
			break;
		case Mobile::CHARGING_PORT:
			mechanic = new Mobile::ChargingPortRepair();
			break;
		default:
			break;
		}
	}
private:
	Mechanic* mechanic;
};
