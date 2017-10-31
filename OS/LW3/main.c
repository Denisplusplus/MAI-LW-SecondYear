#include <stdio.h>
#include <stdlib.h>

     
int cmp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}
   

int** MatrixCreate(int rows, int columns) 
{

    int **matrix = (int**) malloc(sizeof(*matrix) * rows);
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(sizeof(matrix) * columns);
    }
    printf("Input the elements of matrix\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    return(matrix);
}   

int ** MatrixCreateEmpty(int rows, int columns)
{
    int **matrix = (int**) malloc(sizeof(*matrix) * rows);
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(sizeof(matrix) * columns);
    }
    return(matrix);
}


void MatrixPrint(int **a, int rows, int columns)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%3i\t",a[i][j]);
        }
        printf("\n");
    }
}
     

void MatrixFree(int**a, int rows, int columns)
{
    for (int i = 0; i <rows; i++ ) {
        free(a[i]);
    }
    free(a);


}   

int main(void) {
    int rows = 0; int columns = 0; int windowHeight = 0; int windowWidth = 0; int x =0; int i =0; int j =0; 
    int fx = 0; int fy =0;
    printf("Input the number of rows and columns in matrix\n");
    scanf("%d%d", &rows, &columns);
    int** matrix = NULL; matrix = MatrixCreate(rows, columns);    
    int** result = NULL; result = MatrixCreateEmpty(rows, columns);
    for (int i =0; i< rows; i++) {
        for (int j = 0; j < columns; j++) {
            result[i][j]=matrix[i][j];
        }
    }

    MatrixPrint(matrix, rows, columns);
    
    printf("Input the width and height of the window\n");
    scanf("%d%d", &windowHeight, &windowWidth);
    int window[windowHeight* windowWidth];

    int edgeX = (int) (windowWidth / 2);
    int edgeY = (int) (windowHeight / 2);

    for (int x = edgeX; x < columns - edgeX;x++) {
        for (int y = edgeY; y < rows - edgeY;y++) {
            i = 0;
            for (fx = 0; fx < windowWidth; fx++) {
                for (fy = 0; fy < windowHeight; fy++ ) {
                    window[i] = matrix[x + fx - edgeX][y + fy - edgeY];
                    i++;
                }
            }
            qsort(window,windowHeight*windowWidth,sizeof(int),cmp);
            result[x][y] = window[windowWidth * windowHeight / 2];

        }
    }
    MatrixPrint(result, rows, columns);
   
    MatrixFree(matrix, rows, columns);
    MatrixFree(result, rows, columns);
    return 0;
}
