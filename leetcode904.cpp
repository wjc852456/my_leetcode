#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX(a, b) ((a > b)? (a): (b))

int totalFruit(int* tree, int treeSize){
    int classCount = 0;
    int fruitCount = 0;
    int group[2] = {0};
    int result = 0;
    int pos = 0;

    for (int i = 0; i < treeSize; ++i) {
        if (classCount == 0) {
            group[0] = tree[i];
            classCount++;
            fruitCount++;
            continue;
        }
        if (classCount == 1 && tree[i] != group[0]) {
            group[1] == tree[i];
            classCount++;
            fruitCount++;
            pos = i;
            continue;
        }
        if (classCount == 1 && tree[i] == group[0]) {
            fruitCount++;
        }
        if (classCount == 2 && (tree[i] == group[0] || tree[i] == group[1])) {
            fruitCount++;
            if (tree[i] != tree[pos]) {
                pos = i;
            }
        }
        if (classCount == 2 && tree[i] != group[0] || tree[i] != group[1]) {
            result = MAX(result, fruitCount);
            fruitCount = 1;
            classCount = 1;
            i = pos;
            group[0] = tree[i];
        }
    }
    result = MAX(result, fruitCount);
    return result;
}

int main(int argc, char *argv[]){
    int tree[] = {3,3,3,1,2,1,1,2,3,3,4};
    int treeSize = 11;
    int total = totalFruit(tree, treeSize);
    printf("%d", total);
    return 0;
}
