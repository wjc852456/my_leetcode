#include<stdio.h>
#include<string.h>
#include<stdlib.h>


//401.二进制手表

int count1(int num)
{
    int count = 0;
    while (num != 0) {
        num &= (num - 1);
        count++;
    }
    return count;
}

char **readBinaryWatch(int num, int *returnSize)
{
    char **ret = (char **)malloc(190 * sizeof(char *));
    *returnSize = 0;
    int hours;
    int minutes;
    for (int i = 0; i < 12; i++) {
        hours = count1(i);
        for (int j = 0; j < 60; j++) {
            minutes = count1(j);
            if ((hours + minutes) == num) {
                ret[*returnSize] = (char *)malloc(6 * sizeof(char));
                sprintf(ret[*returnSize], "%d:%02d", i, j);
                (*returnSize)++;
            }
        }
    }
    return ret;
}

int main(int argc, char *argv[])
{
    int num = 1;
    int *returnSize;
    char **ret = readBinaryWatch(num, returnSize);
    for (int i = 0; i < *returnSize; i++) {
        printf("%s\n", ret[i]);
    }
    return 0;
}