#include "StrategyPattern_Impl.hpp"

int main()
{
    RepairBusiness repairShop;
    repairShop.damaged(DeviceType::COMPUTER, Computer::MONITOR); // To test ComputerRepair class
    repairShop.damaged(DeviceType::MOBILE, Mobile::SCREEN); // To test MobileRepair class
}
