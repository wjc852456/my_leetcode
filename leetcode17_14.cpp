#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#define print(x) std::cout << #x << " = " << x << std::endl
#if 0
#define MY_DEBUG(index) printf("LINE:[%d], ID:[%d]\n", __LINE__, index)
#else
#define MY_DEBUG(index)
#endif


//面试题17.14. 最小K个数
int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int *smallestK(int *arr, int arrSize, int k, int *returnSize)
{
    if (arr == NULL || arrSize == 0) {
        return NULL;
    }
    *returnSize = k;
    if (k > arrSize) {
        *returnSize = arrSize;
    }
    qsort(arr, arrSize, sizeof(int), cmp);
    return arr;
}



int main(int argc, char *argv[])
{
    int arr[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int arrSize = 8;
    int k = 4;
    int returnSize = 0;
    int *ret = smallestK(arr, arrSize, k, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%d, ", ret[i]);
    }
    return 0;
}
