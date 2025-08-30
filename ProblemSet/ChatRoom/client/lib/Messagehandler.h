#pragma once 
#include <iostream>
#include <queue>
enum class MessageHandlerType {
    RAW,
    INVALID
};

class MessageHandler {
    protected:
        MessageHandlerType type = MessageHandlerType::INVALID;
        std::queue<std::string> inputQueue;
    public:
    MessageHandler() {}
    ~MessageHandler() {}
    virtual int decode(const std::string& input,std::string& output) = 0;
    virtual int encode(const std::string& input,std::string& output) = 0;
};