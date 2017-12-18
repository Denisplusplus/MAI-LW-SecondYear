#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <dlfcn.h>

typedef char Item;


typedef struct Queue {
    int head;
    int last;
    int size;
    char** data;
} Queue;


extern Item* MD5Read(void);
extern bool MD5Check(Item* str);
extern Queue* QueueCreate(int queueSize);
extern bool QueueInsert(Queue* queue, Item* value);
extern Item* QueuePop(Queue* queue);
extern bool QueueIsEmpty(Queue* queue);
extern bool QueueFree(Queue* queue);
extern void QueuePrint(Queue* queue);



#endif