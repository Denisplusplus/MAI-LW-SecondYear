#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "queue.h"

int main(void)
{
    char* error; 

    Item* (*MD5Read)(void);
    bool (*MD5Check)(Item* str);
    Queue* (*QueueCreate)(int queueSize);
    bool (*QueueInsert)(Queue* queue, Item* value);
    Item* (*QueuePop)(Queue* queue);
    bool (*QueueIsEmpty)(Queue* queue);
    bool (*QueueFree)(Queue* queue);
    void (*QueuePrint)(Queue* queue);

    void *libHandle;
    libHandle = dlopen("libqueue.so", RTLD_LAZY);
    if (!libHandle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(-1);
    }

    MD5Read = dlsym(libHandle, "MD5Read");
    MD5Check = dlsym(libHandle, "MD5Check");
    QueueCreate = dlsym(libHandle, "QueueCreate");
    QueueInsert = dlsym(libHandle, "QueueInsert");
    QueuePop = dlsym(libHandle, "QueuePop");
    QueueIsEmpty = dlsym(libHandle, "QueueIsEmpty");
    QueueFree = dlsym(libHandle, "QueueFree");
    QueuePrint = dlsym(libHandle, "QueuePrint");


    if(error = dlerror()) {
        fprintf(stderr, "%s\n", error);
        exit(-2);
    }


    Queue* queue = NULL;
    int capacity = 0;
    
    int choise;

    do {
        printf("Menu:\n");
        printf("1) Create the Queue with certain size\n");
        printf("2) Insert value in the Queue\n");
        printf("3) Pop value from the Queue\n");
        printf("4) Print Queue\n");
        printf("0) Exit\n");
        scanf("%d", &choise);
        switch(choise) {
            case 1:
                printf("Input the capacity\n");
                scanf("%d", &capacity);
                queue = (*QueueCreate)(capacity);
                break;
            case 2:
                printf("Input the value\n");
                char* MD5String = (*MD5Read)();
                if (!(*MD5Check)(MD5String)) {
                    printf("This is not MD5 string\n");
                    break;
                }
                (*QueueInsert)(queue, MD5String);
                free(MD5String);
                break;  
            case 3:
                (*QueuePop)(queue);
                break;  
            case 4:
                (*QueuePrint)(queue);
                break;  
            case 0:
                (*QueueFree)(queue);
                return 0;
        }

    } while(true);

    dlclose(libHandle);
    return 0;
}