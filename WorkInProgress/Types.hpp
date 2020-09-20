#pragma once

#include <string>

typedef std::pair<int, std::string> Message;
static constexpr int SIZE = 8;

enum STATUS
{
	UNDEFINED = -1,
	REQUEST,
	RESPONSE,
	ERROR
};

class Component
{
public:
	virtual void receiveRequest(Message& message) = 0;
};
