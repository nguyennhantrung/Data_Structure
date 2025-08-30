#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include "ClientManager.h"
#include "RawMessageHandler.h"

class Transmission {
    private:
        int server = 0;
        std::thread receiveThread;
        std::thread sendThread;
        std::atomic<bool> threadRunning;
        ClientManager* clientManager = nullptr;
        MessageHandler* messageHandler = nullptr;
    public:
        Transmission(ClientManager* manager, int sock);
        ~Transmission();
        int Start();
        void SendToSever();
        void ReceiveFromServer();
        int PrintOutMessageFromServer(const std::string& message);
};;