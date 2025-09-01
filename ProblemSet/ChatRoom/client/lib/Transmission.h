#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include "ClientManager.h"
#include "MessageHandler.h"

class Transmission {
    private:
        int server = 0;
        ClientManager* clientManager = nullptr;
        MessageHandler* messageHandler = nullptr;

        std::thread receiveThread;
        std::thread sendThread;
        std::atomic<bool> threadRunning;
        
        std::queue<std::string> sendingQueue;
        std::mutex sendingMutex;
        std::condition_variable sendingCv;

    public:
        Transmission(ClientManager* manager, MessageHandler* handler, int sock);
        ~Transmission();
        int Start();
        void SendToSever();
        void ReceiveFromServer();
        int PrintOutMessageFromServer(const std::string& message);
        int AddSendingMessageToQueue(const std::string& message);
};;