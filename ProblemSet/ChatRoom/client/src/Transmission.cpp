#include "../lib/Transmission.h"
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

Transmission::Transmission(ClientManager* manager, MessageHandler* handler, int sock) {
    clientManager = manager;
    messageHandler = handler;
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
    while(threadRunning.load()) {
        string message;
        std::unique_lock<std::mutex> lck(sendingMutex);
        sendingCv.wait(lck, [this]{return !threadRunning.load() || !sendingQueue.empty();});

        if(!threadRunning.load())   continue;
        message = sendingQueue.front();
        sendingQueue.pop();
        lck.unlock();

        ::send(server, message.c_str(), message.length(), 0);
    }
}
void Transmission::ReceiveFromServer() {
    pthread_setname_np(pthread_self(), "ReceiveFromServerThread");
    char buffer[1024] = {0};
    while(threadRunning.load()) {
        ssize_t valread = ::read(server, buffer, 1024);
        if (valread <= 0) {
            LOG("Server disconnected");
            threadRunning.store(false); // Signal other threads to stop
            break;
        }
        std::string receivedMessage(buffer, valread);
        messageHandler->AddToServerQueue(receivedMessage);
        memset(buffer, 0, sizeof(buffer));
    }
}

int Transmission::AddSendingMessageToQueue(const std::string& message) {
    std::unique_lock<mutex> lock(sendingMutex);
    sendingQueue.push(message);
    sendingCv.notify_one();
    return 0;
}