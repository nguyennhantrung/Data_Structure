#include "../lib/Input.h" 
#include "../lib/Log.h" 
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>


InputTerminal::InputTerminal(ClientManager* manager, MessageHandler* handler) {
    clientManager = manager;
    messageHandler = handler;
    inputTerminalThreadRunning.store(false);
}
InputTerminal::~InputTerminal() {
    inputTerminalThreadRunning.store(false);
    if(inputTerminalThread.joinable()) inputTerminalThread.join();
}
int InputTerminal::StartInputTerminal() {
    inputTerminalThreadRunning.store(true);
    inputTerminalThread = std::thread(&InputTerminal::run, this);
    return 0;
}

void InputTerminal::run(){
    pthread_setname_np(pthread_self(), "InputTerminalThread");
    while(inputTerminalThreadRunning) {
        std::string message;
        LOG_INPUT;
        std::getline(std::cin, message);
        messageHandler->AddToConsoleQueue(message);
    }
}