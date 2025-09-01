#include "../lib/Connection.h"

#include <sys/socket.h> // for socket
#include <unistd.h>     // For close

ServerConnection::ServerConnection(ServerManager* manager) {
    serverManager = manager;
}
ServerConnection::~ServerConnection() {
    listenThreadRunning = false;
    if(listenThread.joinable()) listenThread.join();
    close(server_fd);
}

int ServerConnection::OpenConnection () {
    // Creating socket file descriptor
    // AF_INET for IPv4, SOCK_STREAM for TCP, 0 for default protocol
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        LOG("Create socket failed");
        return -1;
    }

    // Forcefully attaching socket to the port
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        LOG("Set socket option failed");
        return -1;
    }
    address.sin_family = AF_INET;        // IPv4 Family address
    address.sin_addr.s_addr = ipAddress; // Listen on all available network interfaces
    address.sin_port = htons(port);      // convert port from host to network type

    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        LOG("bind failed");
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        LOG("listen");
        return -1;
    }

    listenThreadRunning.store(true);
    listenThread = thread(&ServerConnection::ListenClient, this);
    return 0;
}
    
void ServerConnection::ListenClient() {
    pthread_setname_np(pthread_self(), "ListenClientThread");
    LOG("Thread ListenClient running");
    while (listenThreadRunning) {
        // Accept a connection from a client
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            continue; // No client connection
        }

        if(serverManager == nullptr) {
            close(new_socket);
        }
        serverManager->RegisterClient(new_socket);
    }
}

