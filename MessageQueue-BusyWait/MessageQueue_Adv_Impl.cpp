#include "MessageQueue_Impl.h"
MessageManager* MessageManager::instance = nullptr; // Need to initialize static variables outside the class

ClassMonitor monitor;
int main()
{
    monitor.createThread();
    Student1 s1(&monitor);
    Student2 s2(&monitor);
    Student1 s3(&monitor);
    Student2 s4(&monitor);
    s2.submitHomework();
    s4.submitHomework();
    s3.submitHomework();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    s1.submitHomework();
    monitor.exitThread();
}
