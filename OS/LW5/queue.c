#include "queue.h"


Queue* QueueCreate(int queueSize)
{
    Queue* queue = (Queue*) malloc(sizeof(Queue));

    queue->size = queueSize + 1;
    queue->data = (Item **) malloc(sizeof(Item*) * queue->size);
    for (int i = 0; i < queue->size; i++) {
        queue->data[i] = (Item*) malloc(32 * sizeof(Item));
    }
    queue->head = queue->size;
    queue->last = 0;

    return queue;
}

bool QueueInsert(Queue* queue, Item* value)
{   
    if (!queue) {
        printf("Queue doesn't exist\n");
        return false;;
    }
    if ((queue->last + 1) % queue->size == queue->head % queue->size)
        return false;

    strcpy(queue->data[queue->last++], value);
    queue->last %= queue->size;

    return true;
}

Item* QueuePop(Queue* queue)
{   
    if (!queue) {
        printf("Queue doesn't exist\n");
        return NULL;;
    }
    if (QueueIsEmpty(queue)) {
        printf("Queue is empty.\n\n");
        return NULL;
    }

    queue->head %= queue->size;
    return queue->data[queue->head++];
}

bool QueueIsEmpty(Queue* queue)
{
    return (queue->head % queue->size) == queue->last;
}

bool QueueFree(Queue* queue)
{
    if (!queue) {
        return true;
    }
    for (int i = 0; i < queue->size; i++) {
        free(queue->data[i]);
    }
    free((queue)->data);
    free(queue);
    return true;
}
/*
Item* QueueFirst(Queue* queue)
{
    return queue->data[queue->head % queue->size];
}

Item* QueueLast(Queue* queue)
{
    return queue->data[queue->last % queue->size];
}*/



bool MD5Check(Item* str)
{
    if (strlen(str) != 32) {
        return false;
    }
    int k = 0;
    for (int i = 0; i < strlen(str); i++) {
        tolower(str[i]);
        if (((str[i] >= '0') && (str[i] <= '9' )) || ((str[i] >='a' ) && (str[i] <='f'))) {
            k++;
        }
    }
    if (k != strlen(str)) {
        return false;
    }
    return true;
}


void QueuePrint(Queue* queue)
{   
    if (!queue) {
        printf("Queue doesn't exist\n");
        return;
    }    
    if (QueueIsEmpty(queue))
        return;

    Item* value = QueuePop(queue);
    printf("%s\n", value);
    QueuePrint(queue);
    QueueInsert(queue, value);
}


Item* MD5Read()
{
    Item* MD5String = malloc(sizeof(char) *32);
    scanf("%s", MD5String);
    return MD5String;
}
