#include <iostream>
#include "logger.h"

void printNumber() {
    for(int i = 0; i < 100; i++) {
        std::ostringstream msg;
        msg << "Hello guy: " << i;
        LOG(msg.str());
    }
}

int main() {
    // LogManager::GetInstance().setlogFileName("log.txt");
    // LogManager::GetInstance().setLogFileDir("./");
    std::thread  t1(printNumber);
    std::thread  t2(printNumber);
    std::thread  t3(printNumber);
    LOG("Xin chao");
    LOG("How are you");
    t1.join();
    t2.join();
    t3.join();
    return 0;
}