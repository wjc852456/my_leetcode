#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <iostream>
#define print(x) std::cout << #x << " = " << x << std::endl


//695. 岛屿的最大面积
#if 0
#define MY_DEBUG(index) printf("LINE:[%d], ID:[%d]\n", __LINE__, index)
#else
#define MY_DEBUG(index)
#endif

void init_fun(int *array, int size)
{
    for (int i = 0; i < size; i++) {
        array[i] = i;
    }
}

int get_father(int *array, int v)
{
    if (array[v] == v)
        return v;
    array[v] = get_father(array, array[v]);
    return array[v];
}

void merge_ele(int *array, int a, int b)
{
    int a_f = get_father(array, a);
    int b_f = get_father(array, b);

    if (a_f == b_f)
        return;
    if (a_f < b_f)
        array[b_f] = a_f;
    else
        array[a_f] = b_f;
}

void compress(int *array, int size)
{
    for (int i = 0; i < size; i++) {
        array[i] = get_father(array, array[i]);
    }
}

int com_fun(const void *a, const void *b)
{
    return *((int *)a) - *((int *)b);
}

int maxAreaOfIsland(int **grid, int gridSize, int *gridColSize)
{
    
}

int main(int argc, char *argv[])
{
    int gridSize = 8;
    int **grid = (int **)malloc(sizeof(int *)*gridSize);
    int r0[] = {0,0,1,0,0,0,0,1,0,0,0,0,0};
    int r1[] = {0,0,0,0,0,0,0,1,1,1,0,0,0};
    int r2[] = {0,1,1,0,1,0,0,0,0,0,0,0,0};
    int r3[] = {0,1,0,0,1,1,0,0,1,0,1,0,0};
    int r4[] = {0,1,0,0,1,1,0,0,1,1,1,0,0};
    int r5[] = {0,0,0,0,0,0,0,0,0,0,1,0,0};
    int r6[] = {0,0,0,0,0,0,0,1,1,1,0,0,0};
    int r7[] = {0,0,0,0,0,0,0,1,1,0,0,0,0};
    grid[0] = r0;
    grid[1] = r1;
    grid[2] = r2;
    grid[3] = r3;
    grid[4] = r4;
    grid[5] = r5;
    grid[6] = r6;
    grid[7] = r7;
    int ret = maxAreaOfIsland(grid, gridSize, &gridSize);
    printf("%d", ret);
    return 0;
}
