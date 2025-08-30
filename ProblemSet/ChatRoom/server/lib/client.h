#pragma once 
#include <iostream>
#include <unistd.h>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

class ServerManager;

class Client {
    private:
        bool a;
        int _id = 0;
        int _socket = 0;
        std::mutex receiveMutex;
        std::mutex sendMutex;
        std::queue<std::string> receiveMsgQueue;
        std::queue<std::string> sendMsgQueue;
        std::thread receiveThread;
        std::thread sendThread;
        std::atomic<bool> connected{false};
        ServerManager* serverManager = nullptr;
        std::condition_variable sendCv;
    protected:
        void receive(int socket);
        void send(int socket);
    public:
        Client(int id, int socket, ServerManager* manager);
        ~Client() ;
        int EnqueueMessage (std::string sendingMsg);
        std::string DequeueMessage();
};