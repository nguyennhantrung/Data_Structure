#include "../lib/Connection.h"
#include <sys/socket.h> // for socket
#include <netinet/in.h> // for struct of socket
#include <unistd.h>     // For close
#include <thread>
#include <chrono>

ClientConnection::ClientConnection(ClientManager* manager) {
    clientManager = manager;
}
ClientConnection::~ClientConnection() {
    close(socketServer);
}
int ClientConnection::ConnectToServer() {
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Creating socket file descriptor
    socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServer < 0) {
        LOG ("Socket creation error")
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, serverIP.c_str(), &serv_addr.sin_addr) <= 0) {
        LOG("Invalid address/ Address not supported");
        return -1;
    }

    // Connect to the server
    if (connect(socketServer, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        LOG( "Connection Failed");
        return -1;
    }
    LOG("Connected to server" )

    if(clientManager != nullptr)
        clientManager->AddServer(socketServer);
    return 0;
}

int ClientConnection::ReConnectToServer() {
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Creating socket file descriptor
    socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServer < 0) {
        LOG ("Socket creation error")
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, serverIP.c_str(), &serv_addr.sin_addr) <= 0) {
        LOG("Invalid address/ Address not supported");
        return -1;
    }

    // Connect to the server
    LOG("ReConnecting to server . . ." )
    while (connect(socketServer, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    LOG("Connected to server" )

    if(clientManager != nullptr)
        clientManager->AddServer(socketServer);
    return 0;
}
