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


//978. 最长湍流子数组(滑动窗口)
#define MAX(a,b) ((a>b)?(a):(b))

int maxTurbulenceSize(int *A, int ASize)
{
    if (A == NULL || ASize == 0) {
        return 0;
    }
    int l = 0;
    int r = 0;
    int maxLen = r - l + 1;
    bool flag = true;
    for (int i = 0; i < ASize && i + 1 < ASize; ++i) {
        r = i + 1;
        if (A[i] == A[i + 1]) {
            l = i + 1;
        } else if ((A[i] > A[i + 1]) == (!flag)) {
            flag = !flag;
        } else {
            l = i;
            flag = A[i] > A[i + 1];
        }
        maxLen = MAX(maxLen, r - l + 1);
    }
    return maxLen;
}


int main(int argc, char *argv[])
{
    int A[] = {9, 9};
    int ASize = 2;
    int ret = maxTurbulenceSize(A, ASize);
    printf("%d", ret);

    return 0;
}
