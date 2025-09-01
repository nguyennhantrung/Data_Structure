#pragma once 

#include "Log.h"
#include "ClientManager.h"
#include <arpa/inet.h>

class ClientConnection { 
    private:
        const int port = 65432;
        const std::string serverIP = "127.0.0.1";

        struct sockaddr_in address;
        int socketServer = 0;
        ClientManager* clientManager = nullptr;
    public:
        ClientConnection(ClientManager* manager);
        ~ClientConnection();
        int ConnectToServer();
        int ReConnectToServer();
};