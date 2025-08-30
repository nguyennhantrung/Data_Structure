#include <iostream>
#include "lib/log.h"
#include "lib/connection.h"
#include "lib/ServerManager.h"



int main() {
    LOG("Server Start here  !!!");
    ServerManager serverManager;
    ServerConnection serverConnection(&serverManager);
    
    serverConnection.OpenConnection();
    while(true);
    return 0;
}
