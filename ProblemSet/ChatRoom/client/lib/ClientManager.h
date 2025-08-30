#pragma once 
#include <queue>
#include <mutex>
#include "log.h"
class InputTerminal;
class Transmission;

class ClientManager {
    private:
    Transmission* transmission = nullptr;
    InputTerminal* inputTerminal = nullptr;
    std::queue<std::string> inputMessage;
    std::mutex inputMutex;
    public:
    ClientManager();
    ~ClientManager();

    int AddServer(int socket) ;
    int AddInputMessageToQueue(const std::string& message);
    bool GetInputMessageFromQueue(std::string& message);
    int CommandRequest();
};