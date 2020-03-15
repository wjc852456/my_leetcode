#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// 304

typedef struct {
    int **dp;
    int rowSize;
} NumMatrix;


NumMatrix* numMatrixCreate(int** matrix, int matrixSize, int* matrixColSize) 
{
    int i = 0;
    int j = 0;
    int sum1 = 0;
    int sum2 = 0;
    if (matrixSize == 0) return NULL;
    NumMatrix *num = (NumMatrix*)malloc(sizeof(NumMatrix));
    num->dp = (int**)malloc(sizeof(int*) * matrixSize);
    num->rowSize = matrixSize;
    printf("%d", matrix[0][0]);
    for (i = 0; i < matrixSize; i++) {
        num->dp[i] = (int*)malloc(sizeof(int)*(*matrixColSize));
        sum1 += matrix[i][0];
        num->dp[i][0] = sum1;
    }
    for (j = 0; j < *matrixColSize; j++) {
        sum2 += matrix[0][j];
        num->dp[0][j] = sum2;
    }
    for (i = 1; i < matrixSize; i++) {
        for (j = 1; j < *matrixColSize; j++) {
            num->dp[i][j] = num->dp[i-1][j] + 
                            num->dp[i][j-1] - 
                            num->dp[i-1][j-1] + 
                            matrix[i][j];
        }
    }
    return num;
}

int numMatrixSumRegion(NumMatrix* obj, int row1, int col1, int row2, int col2) 
{
    return (obj->dp[row2][col2] - 
    (col1==0 ? 0 : obj->dp[row2][col1-1]) - 
    (row1==0 ? 0 : obj->dp[row1-1][col2]) + 
    ((row1==0 || col1==0) ? 0 : obj->dp[row1-1][col1-1]));
}

void numMatrixFree(NumMatrix* obj) 
{
    if (obj == NULL) {
        return;
    }
    int i = 0;
    for ( ; i < obj->rowSize; i++){
        free(obj->dp[i]);
    }
    free(obj->dp);
    free(obj);
}


int main(int argc, char *argv[])
{
    int matrix[5][5] = { 
                     {3, 0, 1, 4, 2},
                     {5, 6, 3, 2, 1},
                     {1, 2, 0, 1, 5},
                     {4, 1, 0, 1, 7},
                     {1, 0, 3, 0, 5}
                     };
    int matrixSize = 5;
    int matrixColSize = 5;
    NumMatrix* obj = numMatrixCreate((int**)matrix, matrixSize, &matrixColSize);
    int param_1 = numMatrixSumRegion(obj, 2, 1, 4, 3);
    printf("res = %d", param_1);
    numMatrixFree(obj);
    printf("res = %d", param_1);
    return 0;
}