#pragma once 
#include "Log.h"
#include "Client.h"
#include <map>

class ServerConnection;

class ServerManager {
    private:
    ServerConnection* serverConnection = nullptr;
    MessageHandler* messageHandler = nullptr;
    map<int, Client*> clients; // 

    int idCount = 0;
    std::queue<pair<int, std::string>> broadCastQueue;
    std::mutex notifyMutex;
    thread boradcastThread;
    std::atomic<bool> boradcastThreadRunning;
    public:
    ServerManager();
    ~ServerManager() ;
    int Start();
    int GenerateID() ;
    int RegisterClient(int socket);
    void BroadCastToAllClient();
    void AddBroadCastMessage(int id, std::string msg);
};