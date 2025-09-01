#pragma once 
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
class ServerManager;

class MessageHandler {
    private:
        ServerManager* serverManager = nullptr;

        std::queue<std::string> msgFromClientQueue;
        std::thread handleClientMsgThread;
        std::mutex handleClientMsgMutex;
        std::condition_variable ClientMsgCv;
        std::atomic<bool> isRunning;
    public:
        MessageHandler(ServerManager* manager);
        ~MessageHandler();
        void ProcessClientMessage() ;
        int AddToClientQueue(const std::string& message);
        int BuildSetIdRequest(const int& id, std::string& output);
};