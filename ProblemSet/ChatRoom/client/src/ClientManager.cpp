#include "../lib/ClientManager.h"
#include <arpa/inet.h>
#include <unistd.h>

#include "../lib/input.h"
#include "../lib/transmission.h"

ClientManager::ClientManager() {
    inputTerminal = new InputTerminal(this);
    inputTerminal->StartInputTerminal();
}
ClientManager::~ClientManager() {
}

int ClientManager::AddServer(int socket) {
    transmission = new Transmission(this, socket);
    transmission->Start();
    return 0;
}
int ClientManager::AddInputMessageToQueue(const std::string& message) {
    lock_guard<mutex> lock(inputMutex);
    inputMessage.push(message);
    return 0;
}
bool ClientManager::GetInputMessageFromQueue(std::string& message) {
    if(inputMessage.empty())    return 0;
    lock_guard<mutex> lock(inputMutex);
    message = std::move(inputMessage.front());
    inputMessage.pop();
    return 1;
}
int ClientManager::CommandRequest() {
    return 1;
}

int ClientManager::GetId() {
    return id;
}