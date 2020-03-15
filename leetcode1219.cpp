#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX(a, b) ((a > b)? (a) : (b))
// 1219.黄金矿工

int asix[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int visit[15][15] = {0};
int row;
int col;
int tmp;
int ans;

void dfs(int** grid, int i, int j)
{
    if (i < 0 || j < 0 || i > row || j > col || grid[i][j] == 0) {
        return;
    }
    int upd_i;
    int upd_j;
    visit[i][j] = 1;
    tmp += grid[i][j];
    ans = MAX(tmp, ans);
    for (int dir = 0; dir < 4; ++dir) {
        upd_i = i + asix[dir][0];
        upd_j = j + asix[dir][1];
        if (upd_i >=0 && upd_i <= row &&
		    upd_j >=0 && upd_j <= col) {
            if (!visit[upd_i][upd_j] && grid[upd_i][upd_j] > 0) {
                dfs(grid, upd_i, upd_j);
            }
        }
    }
    visit[i][j] = 0;
    tmp -= grid[i][j];
}


int getMaximumGold(int** grid, int gridSize, int* gridColSize)
{
    if (!grid || gridSize == 0 || *gridColSize == 0) {
        return 0;
    }
    row = gridSize - 1;
    col = *gridColSize - 1;
    tmp = 0;
    ans = 0;

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < *gridColSize; ++j) {
            dfs(grid, i, j);
        }
    }
    return ans;
}


int main(int argc, char *argv[]){

    return 0;
}