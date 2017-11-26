#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
     
const int MAXTHREADS =  31177; // cat /proc/sys/kernel/threads-max 


typedef struct matrix {
        int** elements;
        int rows;
        int columns;
     
        int* window;
        int windowHeight;
        int windowWidth;
 } Matrix;
     
     
     
int cmp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}
     
     
Matrix* MatrixCreate() 
{
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    printf("Input the number of rows and columns in matrix\n");
    scanf("%d%d", &(matrix->rows), &(matrix->columns));
    matrix->elements = (int**) malloc(sizeof(*matrix->elements) * matrix->rows);
    for (int i = 0; i < matrix->rows; i++) {
        matrix->elements[i] = (int*)malloc(sizeof(matrix->elements) * matrix->columns);
    }
    printf("Input the elements of matrix\n");
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            scanf("%d", &(matrix->elements[i][j]));
        }
    }
    printf("Input the width and height of the window\n");
    scanf("%d%d", &(matrix->windowHeight), &(matrix->windowWidth));
    if ((matrix->windowHeight % 2 == 0) || (matrix->windowWidth % 2 == 0)) {
        printf("Usage: parameters of window must be odd numbers\n");
        exit(0);
    }
    if (matrix->rows * matrix->columns < matrix->windowHeight * matrix->windowWidth) {
    	printf("Usage: parameters of window must be less then matrix parameters\n");
    	exit(0);
    }
    matrix->window = (int*) malloc(sizeof(*matrix) * matrix->windowHeight * matrix->windowWidth);
    return(matrix);
}   
     
     
void MatrixPrint(Matrix* matrix)
{
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            printf("%d ", matrix->elements[i][j]);
        }
        printf("\n");
    }
}
     
     
void MatrixFree(Matrix* matrix)
{
    for (int i = 0; i < matrix->rows; i++ ) {
        free(matrix->elements[i]);
    }
    free(matrix->elements);
    free(matrix->window);
    free(matrix);
}   

     
void* MatrixFilter(void* argument) 
{

    Matrix* matrix = (Matrix*)argument;
    int z = 0; 
    for(int x = 0; x < matrix->rows - matrix->windowHeight + 1; x++) {
        for(int y = 0; y < matrix->columns - matrix->windowWidth + 1; y++) {
            for (int a = x; a < x + matrix->windowHeight; a++) {
                for (int b = y;b < y + matrix->windowWidth ; b++) {
                    matrix->window[z++]= matrix->elements[a][b];
                }
            }
            if (z == matrix->windowHeight * matrix->windowWidth) { 
                 z = 0;
            }    
            qsort(matrix->window,matrix->windowHeight*matrix->windowWidth,sizeof(int),cmp);
            matrix->elements[x + (int) matrix->windowHeight / 2][y + (int) matrix->windowWidth / 2] = matrix->window[(int) (matrix->windowHeight * matrix->windowWidth / 2)];
        }
    }
    return NULL;
}
int main(int argc, char const *argv[]) {
        if(argc != 2) {
            printf("Usage: enter the number of threads\n");
            exit(0);
        }
        int threadsNum = atoi(argv[1]);
        if (threadsNum <= 0 || threadsNum > MAXTHREADS) {
            printf("Usage: number of threads must be a positive integer number less then 31177\n");
            exit(0);
        }

        pthread_t process[threadsNum];
    	Matrix* matrix = MatrixCreate();
    	MatrixPrint(matrix);
       	printf("\n");
      	
      	int K; 
      	printf("Input the quantity of filters\n");
      	scanf("%d", &K);
      	if (K <= 0 || K > MAXTHREADS || K > threadsNum) {
      		printf("Usage: number of fileters must be a positive integer number less then numbers of threads\n");
            exit(0);
      	}

        for(int iter = 0; iter < K; iter++) {  
            if (pthread_create(&process[iter], NULL, MatrixFilter, (void*) matrix)) {
                perror("pthread_create");
                exit(-1);
            }
            if (pthread_join(process[iter], NULL)) {
                perror("pthread_join");
                exit(-2);
            }

        }

        MatrixPrint(matrix);
        MatrixFree(matrix);
     
        return 0;
    }
