#include "Server.hpp"
#include "RequestBroker.hpp"

RequestBroker req;
int main()
{
    GameServer game(req);
    NetworkManager net(req);
    req.createThread();
    std::string msg = "MESSAGE";
    net.start(msg);
    std::this_thread::sleep_for(std::chrono::seconds(60));
    req.exitThread();
 
}
