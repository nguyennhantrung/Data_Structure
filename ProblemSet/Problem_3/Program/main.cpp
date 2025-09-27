#include <iostream>
#include "LRU.h"
#include <random>
#include <thread>

using namespace std;
#define GET(key) SimpleLRU<int>::GetInstance().getAPI(key);
#define PUT(key, value) SimpleLRU<int>::GetInstance().putAPI(key, value);


int main() {
    srand(0);
    SimpleLRU<int>::GetInstance().setNumLRD(3);

    PUT(1, 10);
    PUT(2, 10);
    PUT(3, 10);
    GET(2);

    return 0;
}
