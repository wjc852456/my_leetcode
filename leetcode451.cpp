#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <iostream>
#define print(x) std::cout << #x << " = " << x << std::endl


typedef struct tagCharPair {
    char id;
    int num;
} CharPair;

int cmp(const void *a, const void *b)
{
    int res1 = ((CharPair *)a)->num;
    int res2 = ((CharPair *)b)->num;
    return res2 - res1;
}

// 451. 根据字符出现频率排序
char *frequencySort(char *s)
{
    if (s == NULL) {
        return NULL;
    }
    CharPair char_list[256];
    int len = strlen(s);
    char *ret = (char *)malloc(len + 1);
    char *top = ret;
    for (int i = 0; i < 256; ++i) {
        char_list[i].id = i;
        char_list[i].num = 0;
    }
    for (int i = 0; i < len; ++i) {
        char_list[s[i]].num++;
    }
    qsort(char_list, 256, sizeof(CharPair), cmp);
    for (int i = 0; i < 256; i++) {
        if (char_list[i].num == 0) {
            break;
        }
        memset(top, char_list[i].id, char_list[i].num);
        top +=  char_list[i].num;
    }
    *top = '\0';
    return ret;
}

int main(int argc, char *argv[])
{
    char s[] = "tree";
    char *ret = frequencySort(s);
    printf("%s", ret);
    return 0;
}