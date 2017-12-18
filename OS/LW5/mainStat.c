#include "queue.h"

void Menu(void);


int main(void)
{
    Queue* queue = NULL;
    int capacity = 0;
    
    int choise;

    do {
        Menu();
        scanf("%d", &choise);
        switch(choise) {
            case 1:
                printf("Input the capacity\n");
                scanf("%d", &capacity);
                queue = QueueCreate(capacity);
                break;
            case 2:
                printf("Input the value\n");
                char* MD5String = MD5Read();
                if (!MD5Check(MD5String)) {
                    printf("This is not MD5 string\n");
                    break;
                }
                QueueInsert(queue, MD5String);
                free(MD5String);
                break;  
            case 3:
                QueuePop(queue);
                break;  
            case 4:
                QueuePrint(queue);
                break;  
            case 0:
                QueueFree(queue);
                return 0;
        }

    } while(true);



    return 0;
}



void Menu(void) 
{
    printf("Menu:\n");
    printf("1) Create the Queue with certain size\n");
    printf("2) Insert value in the Queue\n");
    printf("3) Pop value from the Queue\n");
    printf("4) Print Queue\n");
    printf("0) Exit\n");
}