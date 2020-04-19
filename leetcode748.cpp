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


//748. 最短完整词

void parseWord(char *word, int *arr)
{
    memset(arr, 0, 26 * sizeof(int));
    while (*word != '\0') {
        if (*word >= 'a' && *word <= 'z') {
            arr[*word - 'a']++;
        }
        if (*word >= 'A' && *word <= 'Z') {
            arr[*word - 'A']++;
        }
        word++;
    }
}

bool hasWord(int *licenseWord, int *arr)
{
    for (int i = 0; i < 26; i++) {
        if (licenseWord[i] > arr[i]) {
            return false;
        }
    }
    return true;
}

char *shortestCompletingWord(char *licensePlate, char **words, int wordsSize)
{
    if (licensePlate == NULL) {
        return NULL;
    }
    if (words == NULL || wordsSize == 0) {
        return NULL;
    }
    int parseLicense[26] = {0};
    parseWord(licensePlate, parseLicense);
    char *curWord = NULL;
    char *res = NULL;
    int strLen = 1024;
    for (int i = 0; i < wordsSize; i++) {
        curWord = words[i];
        int tempArr[26] = {0};
        parseWord(curWord, tempArr);
        if (hasWord(parseLicense, tempArr)) {
            if (strlen(curWord) < strLen) {
                strLen = strlen(curWord);
                res = curWord;
            }
        }
    }
    return res;
}


int main(int argc, char *argv[])
{
    char licensePlate[] = "1s3 PSt";
    int wordsSize = 4;
    char word0[] = "step";
    char word1[] = "steps";
    char word2[] = "stripe";
    char word3[] = "stepple";
    char **words = (char **)malloc(wordsSize * sizeof(char *));
    words[0] = word0;
    words[1] = word1;
    words[2] = word2;
    words[3] = word3;
    char *ret = shortestCompletingWord(licensePlate, words, wordsSize);
    printf("%s\n", ret);

    return 0;
}
