#include <iostream>
#include "../lib/DynamicArray.h"

using namespace std;

int main() {
    cout << "Start=======================" << endl;
// Append data
    NNTStructure::List<int> test1;
    test1.append(1);
    test1.append(2);
    test1.append(4);
    test1.append(5);
    cout << "List Test 1: Append data\n\t";
    for(int i = 0; i < test1.size(); i++) {
        cout << test1[i] << " ";
    }
    cout << endl;

// Insert data
    test1.insert(3, 2);
    cout << "List Test 2: Insert data\n\t";
    for(int i = 0; i < test1.size(); i++) {
        cout << test1[i] << " ";
    }
    cout << endl;

// Remove data at index
    test1.removeAt(4);
    cout << "List Test 3: Remove Data at index\n\t";
    for(int i = 0; i < test1.size(); i++) {
        cout << test1[i] << " ";
    }
    cout << endl;

// Remove data value
    test1.remove(2);
    cout << "List Test 4: Remove data value\n\t";
    for(int i = 0; i < test1.size(); i++) {
        cout << test1[i] << " ";
    }
    cout << endl;

// Copy constructor
    NNTStructure::List<int> test2(test1);
    cout << "List Test 5: Copy constructor\n\t";
    for(int i = 0; i < test2.size(); i++) {
        cout << test2[i] << " ";
    }
    cout << endl;

// Copy constructor
    NNTStructure::List<int> test3 = test1;
    cout << "List Test 6: Copy constructor\n\t";
    for(int i = 0; i < test3.size(); i++) {
        cout << test3[i] << " ";
    }
    cout << endl;
    
// Copy assignment
    NNTStructure::List<int> test4;
    test4 = test1;
    cout << "List Test 7: Copy Assignment\n\t";
    for(int i = 0; i < test4.size(); i++) {
        cout << test4[i] << " ";
    }
    cout << endl;

// Move constructor
    NNTStructure::List<int> test5 = std::move(test3);
    cout << "List Test 8: Move Constructor\n\t";
    for(int i = 0; i < test5.size(); i++) {
        cout << test5[i] << " ";
    }
    cout << endl;
    
// Move assignment
    NNTStructure::List<int> test6;
    test6 = std::move(test4);
    cout << "List Test 9: Move Assignment\n\t";
    for(int i = 0; i < test6.size(); i++) {
        cout << test6[i] << " ";
    }
    cout << endl;

// auto iterator
    cout << "List Test 9: Auto Iterator\n\t";
    for(auto& value: test2) {
        cout << value << " ";
    }
    cout << endl; 

    cout << "End=========================" << endl;
    return 0;
}
