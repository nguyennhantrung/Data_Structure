#include "../lib/input.h" 
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>


InputTerminal::InputTerminal(ClientManager* manager) {
    clientManager = manager;
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
        std::cout << ">: ";
        std::getline(std::cin, message);
        if(message[0] == '/') { // command
            // TODO: Add handle command here
        }
        else { // send message
            clientManager->AddInputMessageToQueue(message);
        }
    }
}