#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// 438 找到字符串中所有字母异位词


int findIfAnagrams(char* s1, int* mark, int len)
{
    int mark_[26];
    for (int i = 0; i < 26; ++i) {
        mark_[i] = mark[i];
    }
    for (int i = 0; i < len; ++i) {
        if(--mark_[s1[i] - 'a'] < 0) {
            return -1;
        }
    }
    return 0;
}

int* findAnagrams(char * s, char * p, int* returnSize)
{
    int len_s = strlen(s);
    int len_p = strlen(p);
    *returnSize = 0;
    if (s == NULL || p == NULL || len_s < len_p) {
        return NULL;
    }
    int* ret = (int*)malloc(len_s * sizeof(int));
    char* s1 = (char*)malloc(len_p * sizeof(char));
    int mark[26] = {0};
    for (int i = 0; i < len_p; ++i) {
        mark[p[i] - 'a']++;
    }
    int ifFind;
    for (int i = 0; i < len_s - len_p + 1; ++i) {
        strncpy(s1, &s[i], len_p);
        ifFind = findIfAnagrams(s1, mark, len_p);
        if (ifFind == 0) {
            ret[(*returnSize)++] = i;
        }
    }
    return ret;
}


int main(int argc, char *argv[])
{
    char s[] = "abab";
    char p[] = "ab";
    int* returnSize;
    int* idx = findAnagrams(s, p, returnSize);
    printf("returnSize = %d\n", *returnSize);
    for (int i = 0; i < *returnSize; ++i) {
        printf("idx = %d, ", idx[i]);
    }
    return 0;
}