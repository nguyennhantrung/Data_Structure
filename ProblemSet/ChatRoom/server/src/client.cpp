#include "../lib/client.h"
#include "../lib/ServerManager.h"

#include <iostream>
#include <cstring>
#include <sys/socket.h> // for socket
#include <unistd.h>

void Client::receive(int socket) {
    pthread_setname_np(pthread_self(), "ReceiveFromClientThread");
    char buffer[1024] = {0};
    while (connected) {
        // Read data from the client
        ssize_t valread = ::read(socket, buffer, 1024);
        if (valread <= 0) {
            connected.store(false); 
            break;
        }
        std::string receivedMessage(buffer, valread);
        {
            std::lock_guard<std::mutex> lck(receiveMutex);
            receiveMsgQueue.push(receivedMessage);
        }
        serverManager->NotifyMessageArrived(Client::_id);
        
        memset(buffer, 0, sizeof(buffer));

    }
    // TODO : handle stop thread | error connection
}
void Client::send(int socket) {
    pthread_setname_np(pthread_self(), "SendToClientThread");
    while(connected) {
        std::string sendingMsg;
        {
            std::unique_lock<std::mutex> lock(sendMutex);
            
            // Wait until the queue is not empty or the connection is lost.
            sendCv.wait(lock, [this]{ return !sendMsgQueue.empty() || !connected; });

            // If we are disconnected and the queue is empty, exit the loop.
            if (!connected && sendMsgQueue.empty()) {
                continue;
            }

            // Move the message out of the queue
            sendingMsg = sendMsgQueue.front();
            sendMsgQueue.pop();
        }

        // Send the message outside the mutex lock
        ::send(socket, sendingMsg.c_str(), sendingMsg.length(), 0);
    }
}

Client::Client(int id, int socket, ServerManager* manager): _id(id), _socket(socket), serverManager(manager) {
    connected.store(true); 
    receiveThread = std::thread(&Client::receive, this, socket);
    sendThread = std::thread(&Client::send, this, socket);
}
Client::~Client() {
    connected = false;
    if(receiveThread.joinable()) receiveThread.join();
    if(sendThread.joinable()) sendThread.join();
}
int Client::EnqueueMessage (std::string sendingMsg) {
    {
        std::lock_guard<std::mutex> lck(sendMutex);
        sendMsgQueue.push(sendingMsg);
        sendCv.notify_one();
    }
    return 0;
}
std::string Client::DequeueMessage () {
    std::string receivedMsg;
    {
        std::lock_guard<std::mutex> lck(receiveMutex);
        receivedMsg = std::move(receiveMsgQueue.front());
        receiveMsgQueue.pop();
    }
    return receivedMsg;
}