#pragma once 
#include "ClientManager.h"
#include "MessageHandler.h"
#include <thread>
#include <atomic>
class InputTerminal {
    private:
        std::thread inputTerminalThread;
        std::atomic<bool> inputTerminalThreadRunning;
        ClientManager* clientManager = nullptr;
        MessageHandler* messageHandler = nullptr;
    public:
    InputTerminal(ClientManager* manager, MessageHandler* handler);
    ~InputTerminal();
    int StartInputTerminal();
    void run();
};