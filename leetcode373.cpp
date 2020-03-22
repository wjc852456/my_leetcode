#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <iostream>
#define print(x) std::cout << #x << " = " << x << std::endl
#if 0
#define MY_DEBUG(index) printf("LINE:[%d], ID:[%d]\n", __LINE__, index)
#else
#define MY_DEBUG(index)
#endif

//373. 查找和最小的K对数字(大堆顶)

typedef struct tagHeap {
    int num1;
    int num2;
} Heap;

typedef struct tagHeapTable {
    Heap *heap;
    int curSize;
    int maxSize;
} HeapTable;

HeapTable *HeapTableCreate(int maxSize)
{
    HeapTable *heapTable = (HeapTable *)malloc(sizeof(HeapTable));
    if (heapTable == NULL) {
        return NULL;
    }
    heapTable->heap = (Heap *)malloc(sizeof(Heap) * maxSize);
    memset(heapTable->heap, 0, sizeof(Heap)*maxSize);
    heapTable->curSize = 0;
    heapTable->maxSize = maxSize;
    return heapTable;
}

int Comp(Heap x1, Heap x2)
{
    if (x1.num1 + x1.num2 < x2.num1 + x2.num2) {
        return 1;
    } else {
        return 0;
    }
}

void HeapTableDelete(HeapTable *heapTable)
{
    int i, c;
    Heap x;
    if (heapTable->curSize <= 0) {
        return;
    }
    x = heapTable->heap[heapTable->curSize - 1];
    heapTable->curSize = heapTable->curSize - 1;
    i = 0;
    c = 2 * i + 1;
    while (c < heapTable->curSize) {
        if (c + 1 < heapTable->curSize && Comp(heapTable->heap[c], heapTable->heap[c + 1])) {
            c++;
        }
        if ((heapTable->heap[c].num1 + heapTable->heap[c].num2) <= (x.num1 + x.num2)) {
            break;
        }
        heapTable->heap[i] = heapTable->heap[c];
        i = c;
        c = 2 * i + 1;
    }
    heapTable->heap[i] = x;
}

void HeapTableInsert(HeapTable *heapTable, int num1, int num2)
{
    int i;
    Heap y = {0};
    y.num1 = num1;
    y.num2 = num2;
    if (heapTable == NULL || heapTable->heap == NULL) {
        return;
    }
    // 当堆满的时候判断待插入元素是否比堆顶元素大
    // 1.比堆顶元素大则不插入
    // 2.比堆顶元素小，先删除堆顶元素，然后插入
    if (heapTable->curSize == heapTable->maxSize) {
        if (Comp(heapTable->heap[0], y)) {
            return;
        }
        HeapTableDelete(heapTable);
    }
    heapTable->curSize += 1;
    i = heapTable->curSize;
    while (i > 1 && Comp(heapTable->heap[i / 2 - 1], y)) {
        heapTable->heap[i - 1] = heapTable->heap[i / 2 - 1];
        i /= 2;
    }
    heapTable->heap[i - 1] = y;
}

void HeapTableOutput(HeapTable *heapTable, int **result)
{
    int i;
    if (heapTable == NULL || heapTable->heap == NULL || result == NULL) {
        return;
    }
    for (i = 0; i < heapTable->curSize; i++) {
        result[i][0] = heapTable->heap[i].num1;
        result[i][1] = heapTable->heap[i].num2;
    }
}

void HeapTableDestroy(HeapTable **heapTable)
{
    if ((*heapTable)->heap != NULL) {
        free((*heapTable)->heap);
        (*heapTable)->heap = NULL;
    }
    free(*heapTable);
    *heapTable = NULL;
}

int **kSmallestPairs(int *nums1, int nums1Size, int *nums2, int nums2Size, int k, int *returnSize, int **returnColumnSizes)
{
    int i, j;
    int **returnResult = NULL;
    HeapTable *heapTable = NULL;
    *returnSize = 0;
    *returnColumnSizes = NULL;
    if (nums1Size <= 0 || nums2Size <= 0 || k <= 0) {
        return NULL;
    }
    heapTable = HeapTableCreate(k);
    if (nums1Size * nums2Size < k) {
        *returnSize = nums1Size * nums2Size;
    } else {
        *returnSize = k;
    }
    *returnColumnSizes = (int *)malloc(sizeof(int) * (*returnSize));
    if (*returnColumnSizes == NULL) {
        HeapTableDestroy(&heapTable);
        return NULL;
    }
    for (i = 0; i < *returnSize; ++i) {
        (*returnColumnSizes)[i] = 2;
    }
    returnResult = (int **)malloc((*returnSize) * sizeof(int *));
    for (i = 0; i < (*returnSize); i++) {
        returnResult[i] = (int *)malloc(sizeof(int) * 2);
        memset(returnResult[i], 0, sizeof(int) * 2);
    }
    for (i = 0; i < nums1Size; i++) {
        for (j = 0; j < nums2Size; j++) {
            HeapTableInsert(heapTable, nums1[i], nums2[i]);
        }
    }
    HeapTableOutput(heapTable, returnResult);
    HeapTableDestroy(&heapTable);
    return returnResult;
}

int main(int argc, char *argv[])
{
    int nums1[] = {1, 7, 11};
    int nums1Size = 3;
    int nums2[] = {2, 4, 6};
    int nums2Size = 3;
    int k = 3;
    int a = 0;
    int *returnSize = &a;
    int **returnColumnSizes = &returnSize;
    int **ret = kSmallestPairs( nums1,  nums1Size,  nums2, nums2Size,  k, returnSize, returnColumnSizes);
    for (int i = 0; i < *returnSize; ++i) {
        printf("%d, %d\n", ret[i][0], ret[i][1]);
    }
    return 0;
}
