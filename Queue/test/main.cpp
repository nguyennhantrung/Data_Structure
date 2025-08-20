#include <iostream>
#include "../lib/Queue.h"

using namespace std;

void show(NNTStructure::Queue<int> ll) {
    for(auto& value : ll) {
        cout << value << " ";
    }
}

int main() {
    cout << "Start=======================" << endl;
// Append data
    NNTStructure::Queue<int> test1;
    test1.enqueue(1);
    test1.enqueue(2);
    test1.enqueue(3);
    test1.enqueue(4);
    test1.enqueue(5);
    cout << "List Test 1: Enqueue data\n\t";
    show(test1); // 1 2 4 5
    cout << endl;

// Remove data value
    test1.dequeue();
    test1.dequeue();
    cout << "List Test 2: Dequeue value\n\t";
    show(test1); // 1 2 3 
    cout << endl;

// Copy constructor
    NNTStructure::Queue<int> test2(test1);
    cout << "List Test 3: Copy constructor\n\t";
    show(test2); // 1 2 3
    cout << endl;

// Copy constructor
    NNTStructure::Queue<int> test3 = test1;
    cout << "List Test 4: Copy constructor\n\t";
    show(test3); // 1 2 3  
    cout << endl;
    
// Copy assignment
    NNTStructure::Queue<int> test4;
    test4 = test1;
    cout << "List Test 5: Copy Assignment\n\t";
    show(test4); // 1 2 3
    cout << endl;

// Move constructor
    NNTStructure::Queue<int> test5 = std::move(test3);
    cout << "List Test 6: Move Constructor\n\t";
    show(test5); // 1 2 
    cout << endl;
    
// Move assignment
    NNTStructure::Queue<int> test6;
    test6 = std::move(test4);
    cout << "List Test 7: Move Assignment\n\t";
    show(test6); // 1 2 3
    cout << endl;

    cout << "End=========================" << endl;
    return 0;
}