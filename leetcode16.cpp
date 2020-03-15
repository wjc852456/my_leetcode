#include<stdio.h>
#include<string.h>
#include<stdlib.h>


//401.最接近的三数之和

int comp(const void*a, const void*b)//用来做比较的函数。
{
    return *(int*)a - *(int*)b;
}

int threeSumClosest(int* nums, int numsSize, int target) {
    qsort(nums, numsSize, sizeof(int), comp);
    int closeNum = nums[0] + nums[1] + nums[2];
    for (int i = 0; i < numsSize - 2; i++) {
        int l = i + 1, r = numsSize - 1;
        while (l < r) {
            int tmpSum = nums[i] + nums[l] + nums[r];
            if (abs(target - tmpSum) < abs(target - closeNum)) {
                closeNum = tmpSum;
            }
            if (tmpSum > target)
                r--;
            else if (tmpSum < target)
                l++;
            else
                return target;
        }
    }
    return closeNum;
}


int main(int argc, char *argv[]){
    int nums[4] = {-1, 2, 1, -4};
    int numSize = 4;
    int target = 1;
    int res = threeSumClosest(nums, numSize, target);
    printf("%d", res);
    return 0;
}