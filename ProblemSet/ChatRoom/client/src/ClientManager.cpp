#include "../lib/ClientManager.h"
#include <arpa/inet.h>
#include <unistd.h>

#include "../lib/Input.h"
#include "../lib/Connection.h"
#include "../lib/Transmission.h"
#include "../lib/MessageHandler.h"

ClientManager::ClientManager() {
    clientConnection = new ClientConnection(this);
    messageHandler = new MessageHandler(this);
    inputTerminal = new InputTerminal(this, messageHandler);
    inputTerminal->StartInputTerminal();
}
ClientManager::~ClientManager() {
    if(inputTerminal != nullptr) {
        delete inputTerminal;
        inputTerminal = nullptr;
    }
}

int ClientManager::Start() {
    return clientConnection->ConnectToServer();
}

int ClientManager::AddServer(int socket) {
    transmission = new Transmission(this, messageHandler, socket);
    transmission->Start();
    return 0;
}

int ClientManager::ServerDisconnect() {
    if(transmission != nullptr) {
        delete transmission;
        transmission = nullptr;
    }
    return clientConnection->ReConnectToServer();
}

Transmission* ClientManager::GetTransmission() const {
    return transmission;
}

int ClientManager::GetId() {
    return id;
}

void ClientManager::SetId(const int& _id) {
    id = _id;
}