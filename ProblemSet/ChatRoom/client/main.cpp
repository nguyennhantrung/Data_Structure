#include <iostream>
#include "lib/log.h"
#include "lib/connection.h"
#include "lib/ClientManager.h"



int main() {
    LOG("Server Start here  !!!");
    ClientManager clientManager;
    ClientConnection clientConnection(&clientManager);
    
    if(clientConnection.ConnectToServer() == 0)
        while(true) {}
    return 0;
}
