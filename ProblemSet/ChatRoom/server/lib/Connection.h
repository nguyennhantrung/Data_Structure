#pragma once 

#include <netinet/in.h> // for struct of socket
#include <thread>
#include "Log.h"
#include "ServerManager.h"

class ServerConnection {
    private:
    int server_fd;
    int ipAddress = 0;
    int port = 65432;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    ServerManager* serverManager = nullptr;
    thread listenThread;
    std::atomic<bool> listenThreadRunning;
    public:
    ServerConnection(ServerManager* manager);
    ~ServerConnection();
    int OpenConnection ();
    void ListenClient();
};
