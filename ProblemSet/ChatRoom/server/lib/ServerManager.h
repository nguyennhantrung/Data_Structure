#pragma once 
#include "log.h"
#include "client.h"
#include <map>

class ServerManager {
    private:
    map<int, Client*> clients; // 

    int idCount = 0;
    std::queue<int> incommingQueue;
    std::mutex notifyMutex;
    thread boradcastThread;
    std::atomic<bool> boradcastThreadRunning;
    public:
    ServerManager();
    ~ServerManager() ;
    int GenerateID() ;
    int RegisterClient(int socket);
    void BroadCastToAllClient();
    void NotifyMessageArrived(int id);
};