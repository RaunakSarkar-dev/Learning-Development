#include "WatchdogService_Impl.hpp"

int main()
{
    HealthService hs;
    Patient1 p1(hs);
    Patient2 p2(hs);
    hs.start();
    p2.registerPatient();
    p1.registerPatient();
}
