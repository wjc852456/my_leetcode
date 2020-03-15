#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// 215.数组中的第K个最大元素

int cmp(const void* a, const void* b)
{
    return *(int*)b - *(int*)a;
}


int findKthLargest(int* nums, int numsSize, int k)
{
    qsort(nums, numsSize, sizeof(int), cmp);
    return nums[k-1];
}


int main(int argc, char *argv[])
{
    int arr[] = {3, 2, 1, 5, 6, 4};
    int numsSize = 6;
    int k = 2;
    int ret = findKthLargest(arr, numsSize, k);
    printf("%d", ret);
    return 0;
}