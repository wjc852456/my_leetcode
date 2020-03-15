#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char ret[20];
int idx;

#define FILLROMAN(c, num) \ 
    for ( ; num > 0; num--) { \
        ret[idx++] = c; \
    }

// 12.整数转罗马数字
char* intToRoman(int num)
{
    int idx = 0;
    memset(ret, '\0', 20);
    if (num < 1 || num > 3999) {
        return NULL;
    }
    int M_num = num / 1000;
    num %= 1000;
    FILLROMAN('M', M_num);
    int C_num = num / 100;
    num %= 100;
    if (C_num == 4) {
        ret[idx++] = 'C';
        ret[idx++] = 'D';
    } else if (C_num == 9) {
        ret[idx++] = 'C';
        ret[idx++] = 'M';
    } else {
        int D_num = C_num / 5;
        FILLROMAN('D', D_num);
        C_num %= 5;
        FILLROMAN('C', C_num);
    }
    int X_num = num / 10;
    num %= 10;
    if (X_num == 4) {
        ret[idx++] = 'X';
        ret[idx++] = 'L';
    } else if (X_num == 9) {
        ret[idx++] = 'X';
        ret[idx++] = 'C';
    } else {
        int L_num = X_num / 5;
        FILLROMAN('L', L_num);
        X_num %= 5;
        FILLROMAN('X', X_num);
    }
    int I_num = num;
    if (I_num == 4) {
        ret[idx++] = 'I';
        ret[idx++] = 'V';
    } else if (I_num == 9) {
        ret[idx++] = 'I';
        ret[idx++] = 'X';
    } else {
        int V_num = I_num / 5;
        FILLROMAN('V', V_num);
        I_num %= 5;
        FILLROMAN('I', I_num);
    }
    return ret;
}


int main(int argc, char *argv[])
{
    int num = 90;
    char* roman = intToRoman(num);
    printf("%s", roman);
    return 0;
}