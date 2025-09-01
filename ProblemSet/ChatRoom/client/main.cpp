#include <iostream>
#include "lib/Log.h"
#include "lib/Connection.h"
#include "lib/ClientManager.h"



int main() {
    ClientManager clientManager;
    if(clientManager.Start() != 0)
       return 0;
    while(true) {}
    return 0;
}
