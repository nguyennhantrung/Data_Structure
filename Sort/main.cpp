#include <iostream> 
#include "sort.h"


using namespace std;

const vector<int> sample = {6,5,1,3,8,4,9,7,2,0};
void PrintVector(const vector<int>& input) {
    cout << "---------------" << endl;
    for(auto& v : input) {
        cout << v << " ";
    }
    cout << endl;
}


int main() {
    vector<int> test1 = {6,5,1,3,8,4,9,7,2,0};
    QuickSort(test1, 0, test1.size()-1);
    PrintVector(test1);

    vector<int> test2 = {6,5,1,3,8,4,9,7,2,0};
    MergeSort(test2, 0, test2.size()-1);
    PrintVector(test2);

    vector<int> test3 = {6,5,1,3,8,4,9,7,2,0};
    HeapSort(test3);
    PrintVector(test3);

    cout << "Process End Successfully" << endl;
    return 0;
}