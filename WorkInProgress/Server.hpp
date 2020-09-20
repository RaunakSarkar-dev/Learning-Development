#pragma once

#include <iostream>
#include <string>
#include <thread>
#include "Types.hpp"
#include "RequestBroker.hpp"

class GameServer: public Component
{
private:
	RequestBroker& broker;
public:
	GameServer(RequestBroker& broker)
		:broker(broker)
	{
		broker.addListener(this);
	}

	virtual void receiveRequest(Message& message) override
	{
		while(1){
			std::cout << " Request received" << std::endl;
			processRequest(message);
		}
	}

	void processRequest(Message& message)
	{
		std::cout << " Request processing" << std::endl;
		Message msg;
		msg.first= broker.getMessageId();
		msg.second = "Response";
		sendResponse(msg);
	}

	void sendResponse(Message& message)
	{
		std::cout << " Request served" << std::endl;
		broker.submitResponse(message.second);
	}
};


// This class will act as facilitator to receive requests from outside world and send the response to outside world
class NetworkManager : public Component
{
	RequestBroker& broker;
	int msgId;
public:
	NetworkManager(RequestBroker& broker)
		:broker(broker)
	{
		msgId = 0;
		broker.addListener(this);
	}
	
	virtual void start(std::string& msg) 
	{
		msgId = broker.submitRequest(msg);
		std::cout << " REQUEST" << std::endl;
	}
	void receiveRequest(Message& msg) override
	{
		while(1)
		{
			std::cout << " Response Processed!" << std::endl;
			sendResponse(msg);
		}
	}
	void sendResponse(Message& message)
	{
		if (message.first == msgId)
			std::cout << " Response Sent!" << std::endl;
		else
			std::cout << " Wrong Response!" << std::endl;
		exit(0);
	}
};



