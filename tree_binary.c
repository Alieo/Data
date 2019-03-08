/*************************************************************************
	> File Name: 遍历树的先中后缀.c
	> Author: 
	> Mail: 
	> Created Time: 2018年10月23日 星期二 19时17分55秒
 ************************************************************************/
//遍历树的前中后缀
#include<stdio.h>
#include<stdlib.h>

//结构定义: 节点结构 ..数据域int, 左右子孩子
typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node;

//init : 初始化
Node *init(int data) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = data;
    p->lchild = p->rchild = NULL;
    return p;
}

//clear: 先杀掉左子树, 在杀掉右, 最后杀掉节点
void clear(Node *node) {
    if (node == NULL) return ;
    clear(node->lchild);
    clear(node->rchild);
    free(node);
    return ;
}

//build:创建树(初始化树)
Node *build() {
    Node *root = init(1);
    root->lchild = init(2);
    root->rchild = init(3);
    root->lchild->lchild = init(6);
    root->lchild->rchild = init(7);
    root->lchild->lchild->rchild = init(12);
    root->rchild->lchild = init(5);
    root->rchild->rchild = init(9);
    root->rchild->lchild->lchild = init(10);
    root->rchild->lchild->rchild = init(11);
    return root;
}

//height: 树高: 计算左右子树的树高, 最后比较左右高, 把最高的输出
int height_tree(Node *root) {
    if (root == NULL) return 0;
    int lh = height_tree(root->lchild), rh = height_tree(root->rchild);
    return (lh > rh ? lh : rh) + 1;
}

//preorder前:如果为空,return. 一次打印左子树,右子树
void preorder(Node *root) {
    if (root == NULL) return ;
    printf("%d ", root->data);
    preorder(root->lchild);
    preorder(root->rchild);
    return ;
}

//inorder 中:将pre放中间
void inorder(Node *root) {
    if (root == NULL) return ;
    inorder(root->lchild);
    printf("%d ", root->data);
    inorder(root->rchild);
    return ; 
}

//postor后:pirnt过程放最后, 并将pre改为poster
void postorder(Node *root) {
    if (root == NULL) return ;
    postorder(root->lchild);
    postorder(root->rchild);
    printf("%d ", root->data);
    return ; 
}
//给你一棵树, 统计这棵树的节点个数
int node_num(Node *root) {
    if (root == NULL) return 0;
    return 1 + node_num(root->lchild) + node_num(root->rchild);

}
//给你一棵树, 统计这棵树的叶子节点个数
int leaf_node_num(Node *root) {
    if (root == NULL) return 0;
    if (root->lchild || root->rchild) return leaf_node_num(root->lchild) + leaf_node_num(root->rchild);
    return 1;
}
int main() {
    Node *root = build();
    printf("height(root) = %d\n", height_tree(root));
    preorder(root); printf("\n");
    inorder(root); printf("\n");
    postorder(root); printf("\n");
    printf("The tree has %d nodes.\n", node_num(root));
    printf("The tree has %d leaf nodes.\n", leaf_node_num(root));
    return 0;
}
