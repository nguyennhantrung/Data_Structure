/*
trong C không hỗ trợ overload operator []
vì vậy, chỉ có thể implement get function để get dữ liệu 

để support nhiều loại dữ liệu trong Vector, 
- sử dụng void * (mất type safe vì pahir manual cast)
- sử dụng macro để auto cast type*
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct MyVector {
    unsigned int* value;
    int capacity;
    int size;
};

void MyVectorInit(struct MyVector * vector) {
    if(!vector) return;
    vector->value = malloc(sizeof(unsigned int));
    vector->capacity = 1;
    vector->size = 0;
}
void MyVectorPushBack(struct MyVector * vector, unsigned int value) {
    if(!vector) return;
    if(vector->size == vector->capacity) {
        vector->capacity += 5;
        unsigned int *newValue = malloc(sizeof(unsigned int) * vector->capacity);
        memcpy(newValue, vector->value, vector->size * sizeof(unsigned int));
        free(vector->value);
        vector->value = newValue;
    }
    vector->value[vector->size++] = value;
}
unsigned int MyVectorGet(struct MyVector* vector, unsigned int index) {
    if(!vector) return 0;
    if(index >= vector->size) {
        return 0;
    }
    return vector->value[index];
}

int MyVectorSize(struct MyVector* vector) {
    if(!vector) return 0;
    return vector->size;
}

unsigned int MyVectorPopBack(struct MyVector* vector) {
    if(!vector) return 0;
    return vector->value[--vector->size];
}

void printVector(struct MyVector * Vector) {
    printf("Print Vector\n");
    for(int i = 0; i < MyVectorSize(Vector); i++) {
        printf("%d ", MyVectorGet(Vector, i));
    }
    printf("\n-------------\n");
}

void main() {
    struct MyVector Vector;
    MyVectorInit(&Vector);
    MyVectorPushBack(&Vector, 1);
    MyVectorPushBack(&Vector, 5);
    MyVectorPushBack(&Vector, 2);
    MyVectorPushBack(&Vector, 3);
    MyVectorPushBack(&Vector, 4);

    printVector(&Vector);

    int size = MyVectorSize(&Vector);
    for(int i = 0; i < size; i++) {
        printf("%d ", MyVectorPopBack(&Vector));
    }
    printf("\n");
    printf("end");
}