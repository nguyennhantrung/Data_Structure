#pragma once 
#include <queue>
#include <mutex>
#include "Log.h"
class InputTerminal;
class Transmission;
class MessageHandler;
class ClientConnection;

class ClientManager {
    private:
    int id = -1;
    Transmission* transmission = nullptr;
    MessageHandler* messageHandler = nullptr;
    InputTerminal* inputTerminal = nullptr;
    ClientConnection* clientConnection = nullptr;
    public:
    ClientManager();
    ~ClientManager();
    int Start();
    int GetId();
    void SetId(const int& _id);
    int AddServer(int socket);
    int ServerDisconnect();
    Transmission* GetTransmission() const ;
};