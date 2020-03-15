#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXNUM 1024

int visited[1024];
int idx;

void dfs(int** res, int top, int* buffer, int* nums, int numsSize)
{
    if (top == numsSize - 1 ) {
        for (int i = 0; i < numsSize; ++i) {
            if (visited[i] == 0) {                
                buffer[top] = nums[i];
                for (int j = 0; j < numsSize; ++j ) {
                    res[idx][j] = buffer[j];
                }
            }
        }
        idx++;
        return;
    }
    for (int i = 0; i < numsSize; ++i) {
        if (visited[i] == 0) {
            visited[i] = 1;
            buffer[top] = nums[i];
            dfs(res, top + 1, buffer, nums, numsSize);
            visited[i] = 0;
        }
    }
    return;
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    if (nums == NULL || numsSize == 0) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
    int size = 1;
    for (int i = 1; i <= numsSize; ++i) {
        size *= i;
    }
    *returnSize = size;
    int** res = (int**)malloc(sizeof(int*)*size);
    int *col = (int*)malloc(sizeof(int)* size);
    for (int i = 0; i < size; i++) {
        res[i] = (int*)malloc(numsSize * sizeof(int));
        col[i] = numsSize;
    }
    memset(visited, 0, MAXNUM);
    *returnColumnSizes = col;
    idx = 0;
    int* buffer = (int*)malloc(sizeof(int) * numsSize);
    dfs(res, 0, buffer, nums, numsSize);
    return res;
}


int main(int argc, char *argv[])
{
    int nums[] = {1,2,3};
    int numsSize = 3;
    int a = 0;
    int b = 0;
    int *pb = &b;
    int* returnSize = &a;
    int** returnColumnSizes = &pb;
    int** res = permute(nums, numsSize, returnSize, returnColumnSizes);
    for (int i = 0; i < *returnSize; ++i) {
        for (int j = 0; j < (*returnColumnSizes)[i]; ++j) {
            printf("%d, ", res[i][j]);
        }
        printf("\n");
    }
    

    return 0;
}