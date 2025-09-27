#pragma once
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

int QuickSortPivot(vector<int>& input, int low, int high) {
    int pivot = input[high];
    int left = low - 1;
    int i = low;
    while(i < high) {
        if(input[i] < pivot) {
            swap(input[++left], input[i]);
        }
        i++;
    }
    swap(input[++left], input[high]);
    return left;
}

void QuickSort(vector<int>& input, int low, int high) {
    if(low < high) {
        int pivot = QuickSortPivot(input, low, high);
        QuickSort(input, low, pivot - 1);
        QuickSort(input, pivot + 1, high);
    }
}

void MergeSortPartition(vector<int>& input, int low, int mid, int high) {
    vector<int> v1, v2;
    for(int i = low; i <= mid; i++) {
        v1.push_back(input[i]);
    }
    for(int i = mid+1; i <= high; i++) {
        v2.push_back(input[i]);
    }

    int i = 0, j = 0, k = low;
    while(i < v1.size() && j < v2.size()) {
        if(v1[i] < v2[j]) {
            input[k++] = v1[i++];
        }
        else {
            input[k++] = v2[j++];
        }
    }
    while(i < v1.size()){
        input[k++] = v1[i++];
    }
    while(j < v2.size()){
        input[k++] = v2[j++];
    }
}

void MergeSort(vector<int>& input, int low, int high) {
    if(low < high) {
        int mid = low + (high - low) / 2;
        MergeSort(input, low, mid);
        MergeSort(input, mid+1, high);
        MergeSortPartition(input, low, mid, high);
    }
}




void Heapify(vector<int>& input, int i, int size) {

    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if(left <= size && input[left] > input[largest]) {
        largest = left;
    }
    if(right <= size && input[right] > input[largest]) {
        largest = right;
    }
    if(largest != i) {
        swap(input[i], input[largest]);
        Heapify(input, largest, size);
    }
}

/*
        0
    1       2
3   4       5   6
7 8 9  10 

*/

void HeapSort(vector<int>& input) {
    // Build heapify
    for(int i = input.size()/2-1; i >=0; i--) {
        Heapify(input, i, input.size()-1);
    }

    for(int i = input.size()-1; i > 0; i--) {
        Heapify(input, 0, i);
        swap(input[0], input[i]);
    }
}