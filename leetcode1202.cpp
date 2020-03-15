#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <iostream>
#define print(x) std::cout << #x << " = " << x << std::endl

// 9202. 交换字符串中的元素(并查集)

// 并查集查找父亲元素
int GetParent(int *parent, int child)
{
    if (parent[child] == child) {
        return child;
    }
    int pa = GetParent(parent, parent[child]);
    parent[child] = pa;
    return pa;
}

// 重排一个集合中的所有元素
void ReOrderGrp(int index, char *s, int *flag, int *parent, char *ret)
{
    int charNum[26] = {0};
    int tmp = index;
    while (tmp != -1) {
        flag[tmp] = 1;
        charNum[s[tmp] - 'a']++;
        tmp = parent[tmp];
    }
    tmp = index;
    for (int i = 0; i < 26; i++) {
        if (charNum[i] == 0) {
            continue;
        }

        while (tmp != -1 && charNum[i] > 0) {
            ret[tmp] = 'a' + i;
            charNum[i]--;
            tmp = parent[tmp];
        }
    }
}

char *smallestStringWithSwaps(char *s, int **pairs, int pairsSize, int *pairsColSize)
{
    const int strLen = strlen(s);
    int *parent = (int *)malloc(sizeof(int) * strLen);
    for (int i = 0; i < strLen; i++) {
        parent[i] = i;
    }

    // 构建并查集
    for (int i = 0; i < pairsSize; i++) {
        int i0 = GetParent(parent, pairs[i][0]);
        int i1 = GetParent(parent, pairs[i][1]);

        if (i0 > i1) {
            parent[pairs[i][0]] = i1;
            parent[i0] = i1;
        } else {
            parent[pairs[i][1]] = i0;
            parent[i1] = i0;
        }
    }

    // 同一个集合的元素都归类为同一个root
    for (int i = 0; i < strLen; i++) {
        parent[i] = GetParent(parent, i);
    }

    int nextIndex[strLen];
    memset(nextIndex, -1, sizeof(nextIndex));

    // 一个集合按照编号，第一个指向下一个，最后一个指向-1
    for (int i = strLen - 1; i >= 0; i--) {
        int pa = parent[i];
        parent[i] = nextIndex[pa];
        nextIndex[pa] = i;
    }

    int flag[strLen];       // 对应的元素是否已经处理过了
    memset(flag, 0, sizeof(flag));
    char *ret = (char *)malloc(strLen + 1);

    for (int i = 0; i < strLen; i++) {
        if (flag[i] != 0) {
            continue;
        }
        ReOrderGrp(i, s, flag, parent, ret);
    }

    ret[strLen] = '\0';
    return ret;
}

int main(int argc, char *argv[])
{
    char s[] = "dcab";
    char s2[] = "dcaa";
    int A[] = {1, 2, 3, 4};
    print(sizeof(A + 0));

    return 0;
}