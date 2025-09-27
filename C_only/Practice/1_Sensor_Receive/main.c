#include <stdio.h>
#include <stdlib.h>

struct SensorData {
    union  {
        float valueC;
        int valueA;
        unsigned int valueB;
    };
    union { // nên tạo union để nhanh chóng kiểm tra giá trị chuỗi dữ liệu
        char rawData[4];
        int rawDataA;
        unsigned int rawDataB;
        float rawDataC;
    };
};

struct Sensor {
    char id;
    struct SensorData data;
    int(*process)(struct Sensor* sensor);
};


int processA (struct Sensor* sensor) {
    if(!sensor) return 0;
    sensor->data.valueA = (sensor->data.valueA - 20) / 2;
    return 0;
}
int processB (struct Sensor* sensor) {
    if(!sensor) return 0;
    sensor->data.valueB = (sensor->data.valueB + 10) / 3;
    return 0;
}
int processC (struct Sensor* sensor) {
    if(!sensor) return 0;
    sensor->data.valueC = (sensor->data.valueC + 15.6) / 2.3;
    return 0;
}

struct DatabaseNode {
    char id;
    struct SensorData data;
    unsigned int count;
    struct DatabaseNode* next;
};
struct Database {
    struct DatabaseNode* node;
};

void storeValue (struct Database* db, struct Sensor* sensor) {
    if(!db || !sensor)  return;
    char id = sensor->id;
    
    struct DatabaseNode* currNode = db->node;
    struct DatabaseNode* prevNode = NULL;

    while(currNode != NULL) {
        if(currNode->id == id) {
            // found ID
            if(currNode->data.valueA == sensor->data.valueA) {
                // increase count
                currNode->count++;
                return;
            }
        }

        prevNode = currNode;
        currNode = currNode->next;
    }

    // not found ID
    struct DatabaseNode* newNode = malloc(sizeof(struct DatabaseNode));
    newNode->id = id;
    newNode->data = sensor->data;
    newNode->count = 1;
    newNode->next = NULL;
    if(prevNode == NULL) {
        db->node = newNode;
    }
    else {
        prevNode->next = newNode;
    }
}

void printValue(struct Database* db) {
    if(!db) return;
    struct DatabaseNode* node = db->node;
    while(node != NULL) {
        switch(node->id) {
            case 1:
                printf("Sensor type A (ID = %d): There are %d sensors with the raw value of %d.\n", node->id, node->count, node->data.valueA);
                break;
            case 2:
                printf("Sensor type B (ID = %d): There are %d sensors with the raw value of %d.\n", node->id, node->count, node->data.valueB);
                break;
            case 3:
                printf("Sensor type C (ID = %d): There are %d sensors with the raw value of %g.\n", node->id, node->count, node->data.valueC);
                break;
            default:
                break;
        }
        node = node->next;
    }
}

void main() {
    struct Sensor sensor[] = {
        {1, {.valueA = 20,   .rawData = {0x14, 0x00, 0x00, 0x00}}, processA}, 
        {2, {.valueB = 20,    {0x14, 0x00, 0x00, 0x00}}, processB}, 
        {3, {.valueC = 10.322,  {0xCD, 0xCC, 0x2C, 0x41}}, processC}, 
        {1, {.valueA = 20,    {0x14, 0x00, 0x00, 0x00}}, processA}, 
        {3, {.valueC = 10.3,  {0xCD, 0xCC, 0x2C, 0x41}}, processC}
    };

    struct Database db;
    db.node = NULL;

    for(int i = 0; i < sizeof(sensor) / sizeof(struct Sensor); i++) {
        // printf("i: %d\n" , i);
        if(sensor[i].id == 1) printf("id: %d, value: %d\n", sensor[i].id, sensor[i].data.valueA);
        else if(sensor[i].id == 2) printf("id: %d, value: %d\n", sensor[i].id, sensor[i].data.valueB);
        else if(sensor[i].id == 3) printf("id: %d, value: %g\n", sensor[i].id, sensor[i].data.valueC);
        storeValue(&db, &sensor[i]);
    }
    printValue(&db);
    
    
    printf("hello world\n");
}