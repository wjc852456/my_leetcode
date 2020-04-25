#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

// 301. 删除无效的括号
bool IsValid(char *s)
{
    int top = 0;
    while (*s != '\0') {
        if (*s == '(') {
            top++;
        } else if (*s == ')') {
            top--;
        }
        if (top < 0) {
            return false;
        }
        s++;
    }
    return top == 0;
}


char *DeleteChar(char *s, int id, int strLen)
{
    char *newStr = (char *)malloc(strLen + 1);
    strcpy(newStr, s);
    int i;
    for (i = id; s[i] != '\0'; i++) {
        newStr[i] = s[i + 1];
    }
    newStr[i] = '\0';
    return newStr;
}

bool IsHasStr(char **ret, int returnSize, char *s)
{
    for (int i = 0; i < returnSize; i++) {
        if (strcmp(ret[i], s) == 0 ) {
            return true;
        }
    }
    return false;
}

void Bfs(char *s, int *returnSize, int *visited, int strLen, char **ret, int *suss)
{
    if (*suss == 1) {
        return;
    }
    for (int i = 0; i < strLen; i++) {
        if (visited[i] == 1) {
            continue;
        }
        char *subStr = DeleteChar(s, i, strLen);
        if (IsValid(subStr)) {
            char *tmpStr = (char *)malloc(strlen(subStr) + 1);
            strcpy(tmpStr, subStr);
            *suss = 1;
            if (!IsHasStr(ret, *returnSize, tmpStr)) {
                ret[(*returnSize)++] = tmpStr;
            } else {
                free(tmpStr);
            }
        }
        free(subStr);
    }
    if (*suss == 1) {
        return;
    }
    for (int i = 0; i < strLen; i++) {
        if (visited[i] == 1) {
            continue;
        }
        visited[i] = 1;
        char *subStr = DeleteChar(s, i, strLen);
        Bfs(subStr, returnSize, visited, strLen, ret, suss);
        free(subStr);
        visited[i] = 0;
    }
}

char **removeInvalidParentheses(char *s, int *returnSize)
{
    if (s == NULL) {
        *returnSize = 0;
        return NULL;
    }
    int strLen = strlen(s);
    if (strLen == 0) {
        char **ret = (char **)malloc(sizeof(char *) + 1);
        *ret = s;
        *returnSize = 1;
        return ret;
    }
    int *visited = (int *)malloc(sizeof(int) * strLen);
    memset(visited, 0, sizeof(int)*strLen);
    char **ret = (char **)malloc(strLen * sizeof(char *) + 1);
    *returnSize = 0;
    if (IsValid(s)) {
        (*returnSize)++;
        *ret = s;
        return ret;
    }
    for (int i = 0; i < strLen; i++) {
        if (s[i] != '(' && s[i] != ')') {
            visited[i] = 1;
        }
    }
    int suss = 0;
    Bfs(s, returnSize, visited, strLen, ret, &suss);
    free(visited);
    return ret;
}


int main(int argc, char *argv[])
{
    //char s[] = "(a)())()";
    char s[] = "())))))))))";
    int returnSize = 0;
    char **ans = removeInvalidParentheses(s, &returnSize);
    printf("%d\n", returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", ans[i]);
    }
    for (int i = 0; i < returnSize; i++) {
        free(ans[i]);
    }
    free(ans);
    return 0;
}