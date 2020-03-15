#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// 377 组合总数IV

#define MAX_NUM 100000
int dp[MAX_NUM];

int combinationSum4(int* nums, int numsSize, int target)
{
    if (nums == NULL) {
        return 0;
    }
    if (target == 0) {
        return 0;
    }
    memset(dp, 0, MAX_NUM);
    dp[0] = 1;
    int need;
    long long inc, res;
    for (int i = 1; i <= target; ++i) {
        res = 0;
        for (int j = 0; j < numsSize; ++j) {
            need = i - nums[j];
            inc = need < 0 ? 0 : dp[need];
            res += inc;
        }
        dp[i] = res;
    }
    return dp[target];
}


int main(int argc, char *argv[])
{
    int nums[] = {3, 33, 333};
    int numsSize = 3;
    int target = 10000;
    int ret = combinationSum4(nums, numsSize, target);
    printf("ret = %d", ret);
    return 0;
}