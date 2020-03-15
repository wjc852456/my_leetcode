#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <iostream>
#define print(x) std::cout << #x << " = " << x << std::endl
#if 0
#define MY_DEBUG(index) printf("LINE:[%d], ID:[%d]\n", __LINE__, index)
#else
#define MY_DEBUG(index)
#endif

//695. 岛屿的最大面积(并查集)
#define MAX(a,b) ((a > b)? (a):(b))

int x_axis[] = {0, 0, 1, -1};
int y_axis[] = {1, -1, 0, 0};

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

//int array[104] = {0};
int maxAreaOfIsland(int **grid, int gridSize, int *gridColSize)
{
    int totalSize = gridSize * (*gridColSize);
    int *array = (int *)malloc(totalSize * sizeof(int));
    init_fun(array, totalSize);
    int hasIsland = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < *gridColSize; j++) {
            if (grid[i][j] == 1) {
                hasIsland = 1;
                for (int dir = 0; dir < 4; dir++) {
                    int x_t = i + x_axis[dir];
                    int y_t = j + y_axis[dir];
                    if (x_t < 0 || x_t > gridSize - 1 || y_t < 0 || y_t >  *gridColSize - 1) {
                        continue;
                    }
                    if (grid[x_t][y_t] == 1) {
                        int id = i * (*gridColSize) + j;
                        int id_t = x_t * (*gridColSize) + y_t;
                        merge_ele(array, id, id_t);
                    }
                }
            }
        }
    }
    compress(array, totalSize);
    qsort(array, totalSize, sizeof(int), com_fun);
    int maxArea = 0;
    int tmpArea = 0;
    int flag = array[0];
    for (int i = 0; i < totalSize; i++) {
        if (flag != array[i]) {
            flag = array[i];
            maxArea = MAX(maxArea, tmpArea);
            tmpArea = 1;
        } else {
            tmpArea++;
        }
    }
    if (hasIsland) {
        maxArea = MAX(maxArea, tmpArea);
    } else {
        maxArea = 0;
    }
    return maxArea;
}

int main(int argc, char *argv[])
{
    int gridSize = 8;
    int gridColSize = 13;
    int **grid = (int **)malloc(sizeof(int *)*gridSize);
    int r0[] = {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
    int r1[] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0};
    int r2[] = {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0};
    int r3[] = {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0};
    int r4[] = {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0};
    int r5[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
    int r6[] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0};
    int r7[] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0};
    grid[0] = r0;
    grid[1] = r1;
    grid[2] = r2;
    grid[3] = r3;
    grid[4] = r4;
    grid[5] = r5;
    grid[6] = r6;
    grid[7] = r7;
    int ret = maxAreaOfIsland(grid, gridSize, &gridColSize);
    printf("%d", ret);
    return 0;
}
