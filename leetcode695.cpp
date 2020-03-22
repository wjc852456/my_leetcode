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

//207. 课程表(DFS)

void dfs(int *courseState, int curId, int **prerequisites, int prerequisitesSize, int *hasRing)
{
    if (*hasRing == 1 || courseState[curId] == -1) {
        return;
    }
    if (courseState[curId] == 1) {
        *hasRing = 1;
        return;
    }
    courseState[curId] = 1;
    for (int i = 0; i < prerequisitesSize; i++) {
        if (prerequisites[i][0] == curId) {
            int nextId = prerequisites[i][1];
            if (courseState[nextId] == 1) {
                *hasRing = 1;
                return;
            }
            dfs(courseState, nextId, prerequisites, prerequisitesSize, hasRing);
            if (*hasRing == 1) {
                return;
            }
        }
    }

    courseState[curId] = -1;
}

bool canFinish(int numCourses, int **prerequisites, int prerequisitesSize, int *prerequisitesColSize)
{
    if (prerequisitesSize == 0) {
        return true;
    }
    if (numCourses == 0 || prerequisites == NULL || *prerequisites == NULL) {
        return false;
    }
    if (prerequisitesSize == 0 || numCourses == 1) {
        return true;
    }
    int hasRing = 0;
    int *courseState = (int *)malloc(numCourses * sizeof(int));
    memset(courseState, 0, numCourses * sizeof(int));

    for (int i = 0; i < prerequisitesSize; i++) {
        int initId = prerequisites[i][0];
        dfs(courseState, initId, prerequisites, prerequisitesSize, &hasRing);
        if (hasRing) {
            return false;
        }
    }
    return true;
}


int main(int argc, char *argv[])
{
    int numCourses = 2;
    int prerequisitesSize = 5;
    int prerequisitesColSize = 2;
    int **prerequisites = (int **)malloc(sizeof(int *)*prerequisitesSize);
    int r0[] = {2, 0};
    int r1[] = {1, 0};
    int r2[] = {3, 1};
    int r3[] = {3, 2};
    int r4[] = {1, 3};
    prerequisites[0] = r0;
    prerequisites[1] = r1;
    prerequisites[2] = r2;
    prerequisites[3] = r3;
    prerequisites[4] = r4;
    int **p_null = NULL;
    bool ret = canFinish(numCourses, prerequisites, prerequisitesSize, &prerequisitesColSize);
    printf("%d", ret);
    return 0;
}
