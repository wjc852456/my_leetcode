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

//980. 不同路径 III
#define MAXLEN 20
int visited[MAXLEN][MAXLEN] = {0};
int axis_x[] = {0, 0, 1, -1};
int axis_y[] = {1, -1, 0, 0};

void dfs(int **grid, int gridSize, int *gridColSize, int x, int y, int *visitedNum, int *paths)
{
    if (grid[x][y] == 2) {
        if (*visitedNum == gridSize * (*gridColSize)) { // find a proper path
            (*paths)++;
        }
        return;
    }
    for (int dir = 0; dir < 4; dir++) {
        int x_next = x + axis_x[dir];
        int y_next = y + axis_y[dir];
        if (x_next >= 0 && x_next <= gridSize - 1 &&
                y_next >= 0 && y_next <= *gridColSize - 1 &&
                visited[x_next][y_next] != 1) {
            visited[x_next][y_next] = 1;
            (*visitedNum)++;
            dfs(grid, gridSize, gridColSize, x_next, y_next, visitedNum, paths);
            visited[x_next][y_next] = 0;
            (*visitedNum)--;
        }
    }
}

void Init(int **grid, int gridSize, int *gridColSize, int *x, int *y, int *visitedNum)
{
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < *gridColSize; j++) {
            if (grid[i][j] == 1) {
                *x = i;
                *y = j;
                visited[i][j] = 1;
                (*visitedNum)++;
            }
            if (grid[i][j] == -1) {
                visited[i][j] = 1;
                (*visitedNum)++;
            }
        }
    }
}

int uniquePathsIII(int **grid, int gridSize, int *gridColSize)
{
    if (grid == NULL || gridSize == 0) {
        return 0;
    }
    memset(visited, 0, sizeof(int)*MAXLEN * MAXLEN);
    int x, y;
    int paths = 0;
    int visitedNum = 0;
    Init(grid, gridSize, gridColSize, &x, &y, &visitedNum);
    dfs(grid, gridSize, gridColSize, x, y, &visitedNum, &paths);
    return paths;
}



int main(int argc, char *argv[])
{
    int row0[] = {1, 0, 0, 0};
    int row1[] = {0, 0, 0, 0};
    int row2[] = {0, 0, 2, -1};
    int gridSize = 3;
    int **grid = (int **)malloc(gridSize * sizeof(int *));
    grid[0] = row0;
    grid[1] = row1;
    grid[2] = row2;
    int colSize = 4;
    int *gridColSize = &colSize;
    int ret = uniquePathsIII(grid, gridSize, gridColSize);
    print(ret);
    return 0;
}
