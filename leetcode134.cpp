#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// 93. 复原IP地址

#define TMP_N 128
#define ADDR_LEN 16

bool isIpNum(char* s, int i, int j){
    if(i < j && s[i] == '0'){
        return false;
    }
    
    char buf[4];
    int k = 0;
    while(i <= j){
        buf[k++] = s[i++];
    }
    buf[k] = '\0';
    
    k = atoi(buf);
    if(k > 255){
        return false;
    }
    return true;
}

bool isIpArray(char* s, int data[][3], int size){
    char buf[4];
    int j, k;
    for(int i = 0; i < size; i++){
        if(!isIpNum(s, data[i][0], data[i][1])){
            return false;
        }
        k = 0;
        j = data[i][0];
        while(j <= data[i][1]){
            buf[k++] = s[j++];
        }
        buf[k] = '\0';
        data[i][2] = atoi(buf);
    }
    return true;
}

void dfs(char* s, int start, int data[][3], int size, char** res, int* returnSize){
    if(size >= 4){
        if(size == 4 && s[start] == '\0' && isIpArray(s, data, size)){
            res[*returnSize] = (char*)malloc(sizeof(char*)*(start+4));
            sprintf(res[*returnSize], "%d.%d.%d.%d", data[0][2], data[1][2], data[2][2], data[3][2]);
            (*returnSize)++;
        }
        return ;
    }
    
    
    for(int j = start; s[j] != '\0' && j < start+3; j++){
        if(isIpNum(s, start, j)){
            data[size][0] = start;
            data[size][1] = j;
            dfs(s, j+1, data, size+1, res, returnSize);
        }
    }
}

char ** restoreIpAddresses(char * s, int* returnSize){
    int data[1024][3];
    char** res = (char**)malloc(sizeof(char*)*1024);
    *returnSize = 0;
    
    dfs(s, 0, data, 0, res, returnSize);
    
    return res;
}

int main(int argc, char *argv[])
{
    char input[] = "25525511135";
    int returnSize = 0;
    char** ret = restoreIpAddresses(input, &returnSize);
    for (int i = 0; i < returnSize; ++i) {
        printf("%s\n", ret[i]);
    }
    
    return 0;
}