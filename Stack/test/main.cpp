#include <iostream>
#include "../lib/Stack.h"

using namespace std;

void show(NNTStructure::Stack<int> ll) {
    for(auto& value : ll) {
        cout << value.get() << " ";
    }
}

int main() {
    cout << "Start=======================" << endl;
// Append data
    NNTStructure::Stack<int> test1;
    test1.push(1);
    test1.push(2);
    test1.push(4);
    test1.push(5);
    cout << "List Test 1: Append data\n\t";
    show(test1); // 1 2 4 5
    cout << endl;

// Insert data
    test1.insert(3, 2);
    cout << "List Test 2: Insert data\n\t";
    show(test1); // 1 2 3 4 5 
    cout << endl;

// Remove data value
    test1.pop();
    test1.pop();
    cout << "List Test 4: Remove data value\n\t";
    show(test1); // 1 2 3 
    cout << endl;

// Copy constructor
    NNTStructure::Stack<int> test2(test1);
    cout << "List Test 5: Copy constructor\n\t";
    show(test2); // 1 2 3
    cout << endl;

// Copy constructor
    NNTStructure::Stack<int> test3 = test1;
    cout << "List Test 6: Copy constructor\n\t";
    show(test3); // 1 2 3  
    cout << endl;
    
// Copy assignment
    NNTStructure::Stack<int> test4;
    test4 = test1;
    cout << "List Test 7: Copy Assignment\n\t";
    show(test4); // 1 2 3
    cout << endl;

// Move constructor
    NNTStructure::Stack<int> test5 = std::move(test3);
    cout << "List Test 8: Move Constructor\n\t";
    show(test5); // 1 2 
    cout << endl;
    
// Move assignment
    NNTStructure::Stack<int> test6;
    test6 = std::move(test4);
    cout << "List Test 9: Move Assignment\n\t";
    show(test6); // 1 2 3
    cout << endl;

    cout << "End=========================" << endl;
    return 0;
}