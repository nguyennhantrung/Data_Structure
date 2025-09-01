#include "../lib/ServerManager.h"
#include "../lib/Connection.h"

ServerManager::ServerManager() {
    serverConnection = new ServerConnection(this);
    boradcastThreadRunning.store(false);
}
ServerManager::~ServerManager() {
    boradcastThreadRunning.store(false);
    if(boradcastThread.joinable()) boradcastThread.join();
}

int ServerManager::Start() {
    return serverConnection->OpenConnection();
}

int ServerManager::GenerateID() {
    return idCount++;
}

int ServerManager::RegisterClient(int socket) {
    int id =  GenerateID();
    if(messageHandler == nullptr) {
        messageHandler = new MessageHandler(this);
    }
    clients[id] = new Client(id, socket, this, messageHandler);
    if(boradcastThreadRunning.load() == false) {
        boradcastThreadRunning.store(true);
        boradcastThread = thread(&ServerManager::BroadCastToAllClient, this);
    }
    return 0;
}
void ServerManager::BroadCastToAllClient() {
    pthread_setname_np(pthread_self(), "BroadCastToAllClientThread");
    while(boradcastThreadRunning) {
        if(broadCastQueue.empty())  continue;
        pair<int, std::string> packet;
        {
            std::lock_guard<std::mutex> lck(notifyMutex);
            packet = std::move(broadCastQueue.front());
            broadCastQueue.pop();
        }
        for(auto& client : clients) {
            if(client.first == packet.first)  continue; // No need to broadcast itself
            client.second->EnqueueMessage(packet.second);
        }
    }
}
void ServerManager::AddBroadCastMessage(int id, std::string msg) {
    std::lock_guard<std::mutex> lck(notifyMutex);
    broadCastQueue.push(pair<int, std::string>(id,msg));
}
