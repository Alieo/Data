/*************************************************************************
	> File Name: bing_Union.c
	> Author: 
	> Mail: 
	> Created Time: Sun 20 Jan 2019 04:48:19 PM CST
 ************************************************************************/
/*quick-find算法：
1.基于染色的思想，一开始所有点颜色不同
2.链接两个点的操作，可看成将一种颜色的点染成另一种颜色
3.如果俩点颜色一样，证明联通，否则不连通

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct UnionSet {
    int *color;
    int size;
} UnionSet;

UnionSet *init(int n) {
    UnionSet *u = (UnionSet *)calloc(sizeof(UnionSet), 1);
    u->color = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        u->color[i] = i;
    }
    u->size = n;
    return u;
}

int find(UnionSet *u, int x) {
    return u->color[x];
}

int merge(UnionSet *u, int a, int b) {
    int color_a = find(u, a), color_b = find(u, b);
    if (color_a == color_b) return 0;
    for (int i = 0; i < u->size; i++) {
        if (u->color[i] == color_a) u->color[i] = color_b;
    }
    return 1;
}

void clear(UnionSet *u) {
    if (u == NULL) return ;
    free(u->color);
    free(u);
    return ;
}

void output(UnionSet *u) {
    for (int i = 0; i < u->size; i++) {
        printf("(%d, %d)\t", i, u->color[i]);
        if (i + 1 < u->size && i + 1 % 5 == 0) printf("\n");
    }
    printf("\n\n");
    return ;
}

int main() {
    srand(time(0));
    int op, a, b;
    #define MAX_OP 20
    #define MAX_N 10
    UnionSet *u = init(MAX_N);
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 4;
        a = rand() % MAX_N;
        b = rand() % MAX_N;
        switch (op) {
            case 0: {
                printf("find %d <-> %d = %d\n", a, b, find(u, a) == find(u, b));
            } break;
            default: {
                printf("union %d <-> %d = %d\n", a, b, merge(u, a, b));
            } break;
        }
        output(u);
    }
    return 0;
}

