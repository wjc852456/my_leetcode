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


//1111. 有效括号的嵌套深度(栈)

int *maxDepthAfterSplit(char *seq, int *returnSize)
{
    if (seq == NULL) {
        return NULL;
    }
    int len = strlen(seq);
    *returnSize = len;
    int *ret = (int *)malloc(len * sizeof(int));
    int depth = 0;
    for (int i = 0; i < len; i++) {
        if (seq[i] == '(') {
            depth++;
            ret[i] = depth % 2;
        } else if (seq[i] == ')') {
            ret[i] = depth % 2;
            depth--;
        }
    }
    return ret;
}


int main(int argc, char *argv[])
{
    char seq[] = "(()())";
    int returnSize = 0;
    int *ret = maxDepthAfterSplit(seq, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%d, ", ret[i]);
    }
    return 0;
}
