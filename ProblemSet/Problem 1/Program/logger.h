#pragma once
#include <iostream>
#include <string.h>
#include <mutex>

#include <fstream>      // std::ifstream


#define LOG(logStringMsg) LogManager::GetInstance().Write(logStringMsg);

class LogManager {
    private:
        LogManager() {}
        std::string logFileName = "log.txt";
        std::string logFileDir = "./";
        std::_Ios_Openmode fileMode = std::ios::out;
        std::fstream file;
    public:
        static LogManager& GetInstance() {
            static LogManager instance;
            return instance;
        }
        ~LogManager() {
            if(file.is_open()) {
                std::cout << "Closing file" << std::endl;
                file.close();
            }
        }  

        void setlogFileName(std::string name) {
            logFileName = name;
        }
        void setLogFileDir(std::string dir) {
            logFileDir = dir;
        }
        void setFileMode() {
            
        }
        bool Open() {
            file.open(logFileDir+logFileName, fileMode);
            std::cout << "Opening file" << std::endl;
            if(!file) {
                std::cerr << "Error to open file" << std::endl;
                return false;
            }
            return true;
        }

        void Write(std::string logStringMsg) {
            // Check if log file is ready for writing
            if(!file.is_open()) {
                if(Open() == false) {
                    return;
                }
            }
            // Write to log file
            file << logStringMsg << std::endl;
            std::cout << "Write to file:" << logStringMsg << std::endl;
        }
};
