#include <iostream>
#include <thread>
#include <functional>

using namespace std;

bool clockThreadFunc() {
    return true;
}

int main() {
    thread clockThread;
    thread screenThread;
    thread processThread;

    clockThread = thread(clockThreadFunc);
    screenThread = thread(bind(clockThreadFunc));
    return 0;
}