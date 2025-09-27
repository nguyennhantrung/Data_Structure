#include<stdio.h>
#include<stdlib.h>
#include<bool.h>
#include<pthread.h>
#include<time.h>

/*
    Create a traffic light
    - Goal:
        - Show time counting down
        - Show current light
    - Request:
        - 1 Thread handle screen out (time count and current light)
        - 1 Thread generate clock pulse for 1 second
        - 1 Thread process the clock pulse and apply to time count, light
*/
struct LightTime {
    unsigned char red;
    unsigned char yellow;
    unsigned char green;
};

struct threadArgs {
    pthread_mutex_t* mtx;
    bool* run;
    void* data;
};

void* clockPulsesFunc(void* input) {
    struct threadArgs args = *(void*)input;

    while(args.run) {
        
        pthread_mutex_lock(args.mtx);
        
    }

    sleep(1);
    printf("Hello, I'm New Thread id %d\n", id);
}




int main(int argc, char *argv[]) {
    pthread_mutex_t clockMtx = PTHREAD_MUTEX_INITIALIZER; 
    pthread_t clockThread;
    pthread_t screenThread;
    pthread_t processThread;

    struct LightTime lightTime;
    lightTime.red = 5;
    lightTime.yellow = 2;
    lightTime.green = 7;
    bool clockThreadRun = true;
    struct threadArgs clockThreadArgs;
    clockThreadArgs.clockMtx = &clockMtx;
    clockThreadArgs.run = &clockThreadRun;
    clockThreadArgs.data = (void*)&lightTime;

    pthread_create(&clockThread, NULL, clockPulsesFunc, (void*)clockThreadArgs);


    return 0;
}