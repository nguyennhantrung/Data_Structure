#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
class ClientManager;

class MessageHandler {
    private:
        ClientManager* clientManager = nullptr;

        std::queue<std::string> msgFromServerQueue;
        std::queue<std::string> msgFromConsoleQueue;

        std::thread handleServerMsgThread;
        std::thread handleConsoleMsgThread;

        std::mutex handleServerMsgMutex;
        std::mutex handleConsoleMsgMutex;

        std::condition_variable ServerMsgCv;
        std::condition_variable ConsoleMsgCv;

        std::atomic<bool> isRunning;
    public:
        MessageHandler(ClientManager* manager);
        ~MessageHandler();
        void processServerMessage() ;
        void processConsoleMessage() ;
        int AddToServerQueue(const std::string& message);
        int AddToConsoleQueue(const std::string& message);
};
