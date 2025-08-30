#include "../lib/transmission.h"
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include "../lib/RawMessageHandler.h"
#include "../lib/ProtobufMessageHandler.h"

Transmission::Transmission(ClientManager* manager, int sock) {
    clientManager = manager;
    // messageHandler = new RawMessageHandler();
    messageHandler = new ProtobufMessageHandler();
    server = sock;
};
Transmission::~Transmission() {
    if(receiveThread.joinable()) receiveThread.join();
    if(sendThread.joinable()) sendThread.join();
}
int Transmission::Start() {
    threadRunning.store(true);
    receiveThread = std::thread(&Transmission::ReceiveFromServer, this);
    sendThread = std::thread(&Transmission::SendToSever, this);
    return 0;
}
void Transmission::SendToSever() {
    pthread_setname_np(pthread_self(), "SendToSeverThread");
    string message;
    while(threadRunning.load()) {
        if(clientManager->GetInputMessageFromQueue(message))
        {
            string encodedMessage;
            if (messageHandler->encode(message, clientManager->GetId(), false, encodedMessage) == 0)
                ::send(server, encodedMessage.c_str(), encodedMessage.length(), 0);
            else 
                LOG("Failed To encode and send message");
        }
    }
}
void Transmission::ReceiveFromServer() {
    pthread_setname_np(pthread_self(), "ReceiveFromServerThread");
    char buffer[1024] = {0};
    while(threadRunning.load()) {
        ssize_t valread = ::read(server, buffer, 1024);
        if (valread <= 0) {
            LOG("Server disconnected.");
            threadRunning.store(false); // Signal other threads to stop
            break;
        }
        std::string receivedMessage(buffer, valread);
        PrintOutMessageFromServer(receivedMessage);
        memset(buffer, 0, sizeof(buffer));
    }
}

int Transmission::PrintOutMessageFromServer(const std::string& message) {
    string decodedMessage;
    bool command = false;
    int id = -1;
    messageHandler->decode(message, id, command, decodedMessage);
    if(command == false) {
        std::cout << "[id] >"  << decodedMessage << std::endl;
    }
    // TODO: Handle command here
    return 0;
}
