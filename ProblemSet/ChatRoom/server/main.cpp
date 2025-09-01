#include <iostream>
#include "lib/Log.h"
#include "lib/ServerManager.h"



int main() {
    LOG("Server Start here  !!!");
    ServerManager serverManager;
    serverManager.Start();
    while(true);
    return 0;
}
