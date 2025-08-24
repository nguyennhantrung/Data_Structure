#include <iostream>
#include "logger.h"
int main() {
    LogManager::GetInstance().setlogFileName("log.txt");
    LogManager::GetInstance().setLogFileDir("./");

    LOG("Xin chao");
    LOG("How are you");
    return 0;
}