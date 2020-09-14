#include "CommandPattern_Impl.hpp"

int main()
{
	Remote rem;
	rem.pressButton(&TV::turnOn);
	rem.pressButton(&AC::plus);
	rem.pressButton(&TV::minus);
	rem.pressButton(&AC::turnOff);
}
