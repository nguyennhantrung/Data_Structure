#pragma once
#include <iostream>
#include <string>

class Console {
    private:

    public:
        void Print(const std::string& message) {
            std::cout << "\r---" << message << "---" << std::endl;
            std::cout << ">: " << std::flush;
        }
        void Print(const int& id, const std::string& message) {
            std::cout  << "\r[" << id << "]< " << message << std::endl; 
            std::cout << ">: " << std::flush;
        }
};