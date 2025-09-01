#pragma once
#include <iostream>

using namespace std;

#define LOG(msg) LogManager::GetInstance()->Log(msg);

class LogManager {
    private:
        LogManager() {}
    public:
        static LogManager* GetInstance() {
            static LogManager logManager;
            return &logManager;
        }
        void Log(std::string msg) {
            std::cout << msg << std::endl; 
        }
};