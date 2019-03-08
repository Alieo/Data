/*************************************************************************
	> File Name: 最近公共祖先.c
	> Author: 
	> Mail: 
	> Created Time: 2018年10月23日 星期二 19时35分35秒
 ************************************************************************/
/*
思想:两个一起往上走.
     简单:假设两个节点在同一深度. 一起往上走.
     复杂: 俩深度不同. 先将较深的节点往上走, 走到与短节点同一深度,再一起往上走
*/
#include<stdio.h>
#define MAX_N 1000
#define MAX_K 20
struct  Edge {
    int v, n;  //n:定义一个节点的最大数量
} g[MAX_N << 1];
int head[MAX_N + 5] = {0}, cnt = 0;
//建图(画边): 边等于两倍节点数量, 假设树的结构是双向边,n是下一条边的编号
inline void add(int a, int b) {
//添加了一条从a指向b点的边
    g[++cnt].v = b;
    g[cnt].n = head[a];
    head[a] = cnt;
    return ;
}
//初始化dep数组和gas数组:注意, 一定从1节点开始, 而不是从0节点开始.0节点不用
//gas[i][j] -> i点往上走2^j步, 所能到达的祖先节点编号
int gas[MAX_N][MAX_K], dep[MAX_N];//dep是每个节点的深度
void dfs(int u, int father){//参数1:当前点的坐标.参数2:父节点的坐标
//gas[u][0]:表示往上走到达最近父节点的编号
    gas[u][0] = father;
    dep[u] = dep[father] + 1;
    for (int i = 1; i < MAX_K; i++) {
        // gas[u][i]:表示想求u节点往上跳2的i次幂步. gas[u][i - 1]:表示...2的i-1次幂步. 
        gas[u][i] = gas[gas[u][i - 1]][i - 1];
    }
    for (int i = head[u]; i; i = g[i].n) {
        if (g[i].v == father) continue;
        dfs(g[i].v,u);
    }
//不往回走.
    return ;
}
//求两个节点的最近祖先
int lca(int a, int b) {
    if (dep[b] > dep[a]) {
        //交换a和b的值
        a ^= b;//亦或:若abc中有一个1,abc一定是两个1和一个0, 任意知道两个,即可还原第三个.
        b ^= a;
        a ^= b;
    }
    //做a与b的深度差.
    int l = dep[b] - dep[a];
    for (int i = 0; i < MAX_K; i++) {
        //两个节点对齐
        if ((l & (1 << i))) b = gas[b][i];  
        //倍增方法: 如果a的深度=5, b=10, 所求的深度差l=5.所以b需要跳5步. 5可拆为二进制101.所以当i==0和i==2的时候会网上跳. 所以b跳5步.向上跳了两次.一次1步, 一次4步 
    }
    if (a == b) return a;//a和b深度一样.对齐了之后就是, 可以直接返回
    for (int i = MAX_K - 1; i>=0; i--) {
        if (gas[a][i] != gas[b][i]) a = gas[a][i], b = gas[b][i];//一起往上走.如果往上跳到相同节点. 就不往上跳.若不相等才往上跳.
        //从二进制方面想. 若ab往上跳10步可到达. 10可分解为1010.(倍增) 这类方法可遍历二进制的层数深度
    }
    //否则再向上跳
    return gas[a][0];
}
int main() {
    //n:表示各节点有n-1条边
    int n, a, b;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &a, &b);
        //添加a指向b.b指向a的边.
        add(a, b);
        add(b, a);
    }
    //任意选取节点当根节点不会影响两个节点的最短路径.用1号作为根节点.0是父节点.不断地读入两个坐标.
    dfs(1, 0);
    while(scanf("%d%d", &a, &b) != EOF) {
        printf("lca(%d, %d) = %d, a -> b = %d\n", a, b, lca(a, b), dep[a] + dep[b] - 2 * dep[lca(a, b)]);
    }
    return 0;
}
