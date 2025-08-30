#pragma once 
#include "ClientManager.h"
#include <thread>
#include <atomic>
class InputTerminal {
    private:
        std::thread inputTerminalThread;
        std::atomic<bool> inputTerminalThreadRunning;
        ClientManager* clientManager = nullptr;
    public:
    InputTerminal(ClientManager* manager);
    ~InputTerminal();
    int StartInputTerminal();
    void run();
};