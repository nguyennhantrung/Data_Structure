#include <iostream>
#include "../lib/LinkedList.h"

using namespace std;

void show(NNTStructure::LinkedList<int> ll) {
    while(ll != nullptr)
}

int main() {
    cout << "Start=======================" << endl;
    cout << "List Test 1: Append data\n\t";
    NNTStructure::LinkedList<int> test1;
    test1.append(1);
    test1.append(2);
    test1.append(4);
    test1.append(5);




    cout << "End=========================" << endl;
    return 0;
}