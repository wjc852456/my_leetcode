#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// 71.简化路径

char* simplifyPath(char *path) {
    int length = 0;
    while (path[length] != '\0') {
        length++;
    }
    char *stack = (char *)malloc(sizeof(char) * (length + 2));
    int top = -1;
    stack[++top] = '/';
    for (int i = 0; i <= length; i++) {
        if (path[i] == '/' || (path[i] == '.' && (path[i + 1] == '/' || path[i + 1] == '\0'))) {
            continue;
        } else if (path[i] == '.' && path[i + 1] == '.' && (path[i + 2] == '/' || path [i + 2] == '\0')) { // for "../ or .."
            while (top > 0 && stack[--top] != '/');
            i++;
        } else {
            do {
                stack[++top] = path[i];
            } while(i < length && path[i] != '/' && ++i);
        }
    }
    if (top != 1 && stack[top - 1] == '/') {
        stack[--top] = '\0';
    }
    return stack;
}

int main(int argc, char *argv[])
{
    char str[] = "/a//b////c/d//././/..";
    char *res = simplifyPath(str);
    
    printf("%s", res);
    return 0;
}