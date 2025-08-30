#include "../lib/ServerManager.h"

ServerManager::ServerManager() {
    boradcastThreadRunning.store(false);
}
ServerManager::~ServerManager() {
    boradcastThreadRunning.store(false);
    if(boradcastThread.joinable()) boradcastThread.join();
}

int ServerManager::GenerateID() {
    return idCount++;
}

int ServerManager::RegisterClient(int socket) {
    int id =  GenerateID();
    clients[id] = new Client(id, socket, this);
    if(boradcastThreadRunning.load() == false) {
        boradcastThreadRunning.store(true);
        boradcastThread = thread(&ServerManager::BroadCastToAllClient, this);
    }
    return 0;
}
void ServerManager::BroadCastToAllClient() {
    pthread_setname_np(pthread_self(), "BroadCastToAllClientThread");
    while(boradcastThreadRunning) {
        if(incommingQueue.empty())  continue;
        int id = 0;
        {
            std::lock_guard<std::mutex> lck(notifyMutex);
            id = std::move(incommingQueue.front());
            incommingQueue.pop();
        }
        std::string message = clients[id]->DequeueMessage();
        for(auto& client : clients) {
            if(client.first == id)  continue; // No need to broadcast itself
            client.second->EnqueueMessage(message);
        }
    }
}
void ServerManager::NotifyMessageArrived(int id) {
    std::lock_guard<std::mutex> lck(notifyMutex);
    incommingQueue.push(id);
}
