#pragma once
#include <iostream>
#include <string.h>
#include <mutex>

#include <fstream>

#define LOG(logStringMsg) LogManager::GetInstance()->Write(logStringMsg);

class LogManager {
    private:
        LogManager() {}
        LogManager* logManager = nullptr;
        std::string logFileName;
        std::string logFileDir;
        File file;
    public:
        LogManager* GetInstance() {
            if(logManager == nullptr)
                return new LogManager();
            else 
                return logManager;
        }

        void setlogFileName(std::string name) {
            logFileName = name;
        }
        void setLogFileDir(std::string dir) {
            logFileDir = dir;
        }
        bool isValid() {
            
        }
        void Open()

        void Write(std::string logStringMsg) {
            if(file.isOpen())
        }

    
    
};