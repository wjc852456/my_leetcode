#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//720词典中最长单词

#define branchNum 26

struct TriNode
{
    bool isStr;
    TriNode *next[branchNum];
};

void inSert(TriNode *root, const char *word){
    TriNode *location = root;
    while(*word){
        if (location->next[*word - 'a'] == 0){
            TriNode *newNode = (TriNode*)malloc(sizeof(TriNode));
            newNode->isStr = false;
            memset(newNode->next, 0, sizeof(newNode->next));
            location->next[*word - 'a'] = newNode;
        }
        location = location->next[*word - 'a'];
        word++;
    }
    location->isStr = true;
}

bool search(TriNode *root, const char *word){
    TriNode *location = root;
    while (*word && location!=0)
    {
        location = location->next[*word - 'a'];
        word++;
    }
    return (location!=0 && location->isStr);
}


int cmp(const void * a, const void * b)
{
    
   return strlen((char*)b) - strlen((char*)a);
}


char * longestWord(char (*words)[10], int wordsSize){
    char *res;
    qsort(words, wordsSize, sizeof(char*), cmp);
    printf("%s", words[3]);
    res = words[0];
    return res;
}


int main(int argc, char *argv[]){
    char words[5][10] = {"wo","w","worl","wor", "world"};
    char *res = longestWord(words, 5);
    //printf("%s", res);
    return 0;
}