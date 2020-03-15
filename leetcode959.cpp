#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <iostream>
#define print(x) std::cout << #x << " = " << x << std::endl


// 959. 由斜杠划分区域
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

int regionsBySlashes(char **grid, int gridSize)
{
    int grid_cnt = gridSize * gridSize * 4;
    int c;
    int r;
    int *array = (int *)malloc(sizeof(int) * grid_cnt);
    int flag;
    int cnt = 1;

    MY_DEBUG(1);
    init_fun(array, grid_cnt);
    MY_DEBUG(grid_cnt);
    MY_DEBUG(gridSize);
    for (int i = 0; i < grid_cnt; i += 4) {
        c = i / (4 * gridSize);
        r = i / 4;
        r = r % gridSize;

        MY_DEBUG(c);
        MY_DEBUG(r);

        if (grid[c][r] == '\\') {
            merge_ele(array, i, i + 1);
            merge_ele(array, i + 2, i + 3);
        } else if (grid[c][r] == '/') {
            merge_ele(array, i, i + 3);
            merge_ele(array, i + 1, i + 2);
        } else { //(grid[c][r] = ' ')
            merge_ele(array, i, i + 1);
            merge_ele(array, i + 1, i + 2);
            merge_ele(array, i + 2, i + 3);
        }
    }

    MY_DEBUG(2);
    for (int i = 0; i < gridSize; i++) {//行
        for (int j = 0; j < gridSize - 1; j++) {//列
            int index = 1 + j * 4 + i * 4 * gridSize;
            MY_DEBUG(index);
            merge_ele(array, index, index + 6);
        }
    }

    MY_DEBUG(3);
    for (int i = 0; i < gridSize - 1; i++) {//列
        for (int j = 0; j < gridSize; j++) {//行
            int index = 2 + j * 4 + i * 4 * gridSize;
            MY_DEBUG(i);
            MY_DEBUG(j);
            MY_DEBUG(index);
            merge_ele(array, index, index + (gridSize - 1) * 4 + 2);
        }
    }

    MY_DEBUG(4);
    compress(array, grid_cnt);
    qsort(array, grid_cnt, sizeof(int), com_fun);
    flag = array[0];
    for (int i = 0; i < grid_cnt; i++) {
        MY_DEBUG(array[i]);
        if (flag != array[i]) {
            cnt++;
            flag = array[i];
        }
    }
    MY_DEBUG(5);
    return cnt;
}

int main(int argc, char *argv[])
{
    int gridSize = 2;
    char **grid = (char **)malloc(sizeof(char *)*gridSize);
    char t1[] = "/\\";
    char t2[] = "\\/";
    grid[0] = t1;
    grid[1] = t2;
    int ret = regionsBySlashes(grid, gridSize);
    printf("%d", ret);
    return 0;
}
