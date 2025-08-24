#pragma once
#include <iostream>
#include <string.h>
#include <fstream>      // std::fstream, std::ifstream, std::ofstream
#include <sstream>
#include <ctime>
#include <thread>
#include <queue>

#include <mutex>
#include <condition_variable>
#include <atomic>
// #define LOG(logStringMsg) LogManager::GetInstance().Write(logStringMsg);
#define LOG(logStringMsg) LogManager::GetInstance().Log(std::this_thread::get_id(), logStringMsg);


class LogManager {
    private:
        std::string logFileName = "log.txt";
        std::string logFileDir = "./";
        std::_Ios_Openmode fileMode = std::ios::out;
        std::fstream file;
        time_t timestamp;

        std::queue<std::pair<std::thread::id, std::string>> logQueue;
        std::condition_variable cv;
        
        std::atomic<bool> running{true};
        std::mutex mtx;
        std::thread logThread;

        void LogHandler() {
        while (running || !logQueue.empty()) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&]{ return !logQueue.empty() || !running; });

            while (!logQueue.empty()) {
                auto msg = logQueue.front();
                logQueue.pop();
                lock.unlock();
                Write(msg);     // write one log
                lock.lock();
            }
        }
    }
        LogManager() {
            logThread = std::thread(&LogManager::LogHandler, this);
        }
    public: // Construction
        static LogManager& GetInstance() {
            static LogManager instance;
            return instance;
        }
        ~LogManager() {
            running = false;
            cv.notify_all();
            if (logThread.joinable())
                logThread.join();
            if (file.is_open())
                file.close();
        }  
    public: // Configuration
        void setlogFileName(std::string name) {
            logFileName = name;
        }
        void setLogFileDir(std::string dir) {
            logFileDir = dir;
        }
    public: // Common functions
        bool Open() {
            file.open(logFileDir+logFileName, fileMode);
            std::cout << "Opening file" << std::endl;
            if(!file) {
                std::cerr << "Error to open file" << std::endl;
                return false;
            }
            return true;
        }
        const std::string getCurrentTime() {
            std::time_t t = std::time(0);   // Get the time now
            std::tm* now = std::localtime(&t);
            std::ostringstream oss;
            oss << (now->tm_year + 1900) << '-'
                << (now->tm_mon + 1) << '-'
                << now->tm_mday << " "
                << now->tm_hour << ":"
                << now->tm_min << ":"
                << now->tm_sec;
            return oss.str();
        }

        void Log(std::thread::id id, std::string msg){
            {
                std::lock_guard<std::mutex> lock(mtx);
                logQueue.emplace(id, msg);
            }
            cv.notify_one();
        }


        void Write(std::string logStringMsg) {
            // Check if log file is ready for writing
            if(!file.is_open()) {
                if(Open() == false) {
                    return;
                }
            }
            // Write to log file
            std::ostringstream outputMsg;
            outputMsg << "[Thread: ";
            outputMsg << std::this_thread::get_id();
            outputMsg << "]";
            outputMsg << "[";
            outputMsg << getCurrentTime();
            outputMsg << "] ";
            outputMsg << logStringMsg;
            file << outputMsg.str() << std::endl;
            std::cout << "Write to file:" << outputMsg.str() << std::endl;
        }

        void Write(std::pair<std::thread::id, std::string> msg) {
            // Check if log file is ready for writing
            if(!file.is_open()) {
                if(Open() == false) {
                    return;
                }
            }
            // Write to log file
            std::ostringstream outputMsg;
            outputMsg << "[Thread: ";
            outputMsg << msg.first;
            outputMsg << "]";
            outputMsg << "[";
            outputMsg << getCurrentTime();
            outputMsg << "] ";
            outputMsg << msg.second;
            file << outputMsg.str() << std::endl;
            std::cout << "Write to file:" << outputMsg.str() << std::endl;
        }
};
