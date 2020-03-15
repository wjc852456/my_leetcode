#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

// 526 优美的排列
#define MAXNUM 16
int dp[MAXNUM];
int visited[MAXNUM];
int g_count;

void dfs(int idx, int N)
{
    if (idx == (N+1)){
        g_count++;
        return;
    }
    for (int i = 1; i <= N; ++i){
        if (!visited[i]){    
            if (idx % i == 0 || i % idx == 0) {
                visited[i] = 1;
                dfs(idx+1, N);
                visited[i] = 0;
            }
        }
    }
    return;
}

int countArrangement(int N)
{
    memset(dp, 0, MAXNUM);
    memset(visited, 0, MAXNUM);
    g_count = 0;
    dfs(1, N);
    return g_count;
}


int main(int argc, char *argv[])
{
    int N = 6;
    int res = countArrangement(N);
    printf("%d\n", res);
    return 0;
}