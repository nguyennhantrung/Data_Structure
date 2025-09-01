#pragma once
#include <iostream>

using namespace std;

#define LOG(msg) LogManager::GetInstance()->Log(msg);
#define LOG_MSG(id, msg) LogManager::GetInstance()->Log(id, msg);
#define LOG_INPUT LogManager::GetInstance()->LogInput();

class LogManager {
    private:
        LogManager() {}
    public:
        static LogManager* GetInstance() {
            static LogManager logManager;
            return &logManager;
        }
        void Log(const std::string& message) {
            std::cout << "\r--- " << message << " ---" << std::endl;
            std::cout << ">: " << std::flush;
        }
        void Log(const int& id, const std::string& message) {
            std::cout  << "\r[" << id << "]< " << message << std::endl; 
            std::cout << ">: " << std::flush;
        }
        void LogInput() {
            std::cout << ">: " << std::flush;
        }
};