#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <iostream>
#define print(x) std::cout << #x << " = " << x << std::endl

// 773. 滑动谜题

#define MAX_M 2
#define MAX_N 3
#define MAX_LEN 50000
#define MAX_QUEUE_LEN 10000

struct SNode {
    int lev;
    int matrix[MAX_M][MAX_N];
};

static bool g_visited[MAX_LEN];

static struct SNode g_tmpRecord[MAX_N];
static struct SNode g_queue[MAX_QUEUE_LEN];

static int GetNum(struct SNode *p)
{
    int ans = 0;
    int i, j;
    int table[MAX_M][MAX_N] = { 0 };

    for (i = 0; i < MAX_M; i++) {
        for (j = 0; j < MAX_N; j++) {
            table[i][j] = pow(6, i * MAX_N + j);
        }
    }

    for (i = 0; i < MAX_M; i++) {
        for (j = 0; j < MAX_N; j++) {
            ans += p->matrix[i][j] * table[i][j];
        }
    }
    return ans;
}

static void Swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

static bool IsValid(int i, int j)
{
    if (i < 0 || i >= MAX_M ||
            j < 0 || j >= MAX_N) {
        return false;
    }
    return true;
}

static int GetNext(struct SNode p)
{
    int i, j, k, outIndex;
    int iGo[] = {-1, 0, 1, 0};
    int jGo[] = {0, 1, 0, -1};

    outIndex = 0;

    for (i = 0; i < MAX_N; i++) {
        memcpy(&g_tmpRecord[i], &p, sizeof(p));
    }

    for (i = 0; i < MAX_M; i++) {
        for (j = 0; j < MAX_N; j++) {
            if (p.matrix[i][j] == 0) {
                for (k = 0; k < 4; k++) {
                    if (!IsValid(i + iGo[k], j + jGo[k])) {
                        continue;
                    }
                    Swap(&g_tmpRecord[outIndex].matrix[i][j], &g_tmpRecord[outIndex].matrix[i + iGo[k]][j + jGo[k]]);
                    outIndex++;
                }
                break;
            }
        }
    }
    return outIndex;
}

static bool IsOk(struct SNode *in, struct SNode *out)
{
    int i, j;

    for (i = 0; i < MAX_M; i++) {
        for (j = 0; j < MAX_N; j++) {
            if (in->matrix[i][j] != out->matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}

static int Bfs(struct SNode *in, struct SNode *out)
{
    int front, rear, num, k, curLev, inputNum;
    struct SNode *p;

    front = 0;
    rear = 0;

    memcpy(&g_queue[rear], in, sizeof(*in));
    num = GetNum(in);
    g_visited[num] = true;
    rear++;

    while (front != rear) {
        p = &g_queue[front];
        curLev = p->lev;
        front++;
        if (IsOk(p, out)) {
            return curLev;
        }
        inputNum = GetNext(*p);
        for (k = 0; k < inputNum; k++) {
            num = GetNum(&g_tmpRecord[k]);
            if (g_visited[num]) {
                continue;
            }
            g_tmpRecord[k].lev = curLev + 1;
            memcpy(&g_queue[rear], &g_tmpRecord[k], sizeof(struct SNode));
            g_visited[num] = true;
            rear++;
        }
    }
    return -1;
}

int slidingPuzzle(int **board, int boardSize, int *boardColSize)
{
    struct SNode in, out;
    int i, j;

    memset(g_visited, 0, sizeof(g_visited)); // visited all 0
    memset(g_tmpRecord, 0, sizeof(g_tmpRecord));
    memset(&in, 0, sizeof(in));
    memset(&out, 0, sizeof(out));

    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < *boardColSize; j++) {
            in.matrix[i][j] = board[i][j];
            out.matrix[i][j] = (i * MAX_N + j + 1) % 6;
        }
    }

    return Bfs(&in, &out);
}

int main(int argc, char *argv[])
{
    int *rol0 = (int *)malloc(3 * sizeof(int));
    int *rol1 = (int *)malloc(3 * sizeof(int));
    int **board = (int **)malloc(2 * sizeof(int *));
    board[0] = rol0;
    board[1] = rol1;
    board[0][0] = 1;
    board[0][1] = 2;
    board[0][2] = 3;
    board[1][0] = 4;
    board[1][1] = 0;
    board[1][2] = 5;
    int boardColSize = 3;
    slidingPuzzle(board, 2, &boardColSize);
    return 0;
}