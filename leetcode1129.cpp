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


//1129. 颜色交替的最短路径(BFS)

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int *shortestAlternatingPaths(int n, int **red_edges, int red_edgesSize, int *red_edgesColSize, int **blue_edges, int blue_edgesSize, int *blue_edgesColSize, int *returnSize)
{
    // Graph Info
    int **redGraph = (int **)malloc(sizeof(int *) * n);
    int **blueGraph = (int **)malloc(sizeof(int *) * n);
    int *redGraphSize = (int *)malloc(sizeof(int) * n);
    int *blueGraphSize = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
        redGraphSize[i] = 0;
        blueGraphSize[i] = 0;
        redGraph[i] = (int *)malloc(sizeof(int) * n);
        blueGraph[i] = (int *)malloc(sizeof(int) * n);
    }
    for (int i = 0; i < red_edgesSize; ++i) {
        int *tmp = red_edges[i];
        redGraph[tmp[0]][redGraphSize[tmp[0]]++] = tmp[1];
    }
    for (int i = 0; i < blue_edgesSize; ++i) {
        int *tmp = blue_edges[i];
        blueGraph[tmp[0]][blueGraphSize[tmp[0]]++] = tmp[1];
    }
    // Shortest path for vertex end with red/blue edge
    int *redPath = (int *)malloc(sizeof(int) * n);
    int *bluePath = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
        redPath[i] = -1;
        bluePath[i] = -1;
    }
    redPath[0] = bluePath[0] = 0;
    // Queue for BFS
    int **redQueue = (int **)malloc(sizeof(int *) * 2);
    int **blueQueue = (int **)malloc(sizeof(int *) * 2);
    for (int i = 0; i < 2; ++i) {
        redQueue[i] = (int *)malloc(sizeof(int) * n);
        blueQueue[i] = (int *)malloc(sizeof(int) * n);
    }
    int redQueueSize[2] = {0, 1};
    int blueQueueSize[2] = {0, 1};
    redQueue[1][0] = 0;
    blueQueue[1][0] = 0;
    int path = 0;
    // BFS
    while (redQueueSize[1] || blueQueueSize[1]) {
        ++path;
        // Switch two queues
        redQueueSize[0] = redQueueSize[1];
        redQueueSize[1] = 0;
        blueQueueSize[0] = blueQueueSize[1];
        blueQueueSize[1] = 0;
        int *tmp = redQueue[0];
        redQueue[0] = redQueue[1];
        redQueue[1] = tmp;
        tmp = blueQueue[0];
        blueQueue[0] = blueQueue[1];
        blueQueue[1] = tmp;
        // BFS add to queue
        for (int i = 0; i < redQueueSize[0]; ++i) {
            int red = redQueue[0][i];
            for (int j = 0; j < blueGraphSize[red]; ++j) {
                int nextBlue = blueGraph[red][j];
                if (bluePath[nextBlue] >= 0) continue;
                bluePath[nextBlue] = path;
                blueQueue[1][blueQueueSize[1]++] = nextBlue;
            }
        }
        for (int i = 0; i < blueQueueSize[0]; ++i) {
            int blue = blueQueue[0][i];
            for (int j = 0; j < redGraphSize[blue]; ++j) {
                int nextRed = redGraph[blue][j];
                if (redPath[nextRed] >= 0) continue;
                redPath[nextRed] = path;
                redQueue[1][redQueueSize[1]++] = nextRed;
            }
        }
    }
    // return shortest path in two paths
    for (int i = 0; i < n; ++i) {
        if (redPath[i] == -1 && bluePath[i] >= 0)
            redPath[i] = bluePath[i];
        else if (redPath[i] * bluePath[i] >= 0 && redPath[i] > bluePath[i])
            redPath[i] = bluePath[i];
    }
    *returnSize = n;
    return redPath;
}


int main(int argc, char *argv[])
{
    int n = 3;
    int red_edge0[] = {0, 1};
    int red_edge1[] = {0, 2};
    int red_edgesSize = 2;
    int red_edgesColSize = 2;
    int **red_edges = (int **)malloc(red_edgesSize * sizeof(int *));
    red_edges[0] = red_edge0;
    red_edges[1] = red_edge1;

    int blue_edge0[] = {1, 0};
    int blue_edgesSize = 1;
    int blue_edgesColSize = 2;
    int **blue_edges = (int **)malloc(blue_edgesSize * sizeof(int *));
    blue_edges[0] = blue_edge0;

    int returnSize = 0;
    int *ret = shortestAlternatingPaths(n, red_edges, red_edgesSize, &red_edgesColSize, blue_edges, blue_edgesSize, &blue_edgesColSize, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%d, ", ret[i]);
    }

    return 0;
}
