/*************************************************************************
	> File Name: tree_AVL.c
	> Author: 
	> Mail: 
	> Created Time: Sat 08 Dec 2018 03:41:51 PM CST
 ************************************************************************/
//主函数随机数插入变成AVL树
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define MAX(a, b) ({\
    __typeof(a) _a = (a);\
    __typeof(b) _b = (b);\
    _a > _b ? _a : _b;\
})
typedef struct Node {
    int key;
    struct Node *lchild, *rchild;
    int h;
} Node;

//虚拟节点：防止报错
Node *NIL;

__attribute__((constructor))
void init_nil() {
    NIL = (Node *)malloc(sizeof(Node));
    NIL->key = 0;
    NIL->lchild = NIL->rchild = NIL;
    NIL->h = 0;
}
Node *init(int key) {
    Node *p =  (Node *)malloc(sizeof(Node));
    p->lchild = p->rchild = NIL;
    p->h = 1;
    p->key = key;
    return p;
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    //root节点的更新一定要先于temp节点的更新
    root->h = MAX(root->lchild->h, root->rchild->h) + 1;
    temp->h = MAX(temp->lchild->h, temp->rchild->h) + 1;
    return temp;
}
Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    //root节点的更新一定要先于temp节点的更新
    root->h = MAX(root->lchild->h, root->rchild->h) + 1;
    temp->h = MAX(temp->lchild->h, temp->rchild->h) + 1;
    return temp;
}
Node *maintain(Node *root) {
    if (abs(root->lchild->h - root->rchild->h) < 2) return root;
    //说明他是L类型的
    if (root->lchild->h > root->rchild->h) {
        //LR
        if (root->lchild->lchild->h < root->lchild->rchild->h) {
            root->lchild = left_rotate(root->lchild);
        }//只要是L开头, 一定会是右旋结束, 反之, 一定会是左旋结束
        root = right_rotate(root);
    } else {
        //RL
        if (root->rchild->lchild->h > root->rchild->rchild->h) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    return root;
}

Node *insert(Node *root, int key) {
    if (root == NIL) return init(key);
    if (root->key == key) return root;
    if (root->key < key) {
        root->rchild = insert(root->rchild, key);
    } else {
        root->lchild = insert(root->lchild, key);
    }
    root->h = MAX(root->lchild->h, root->rchild->h) + 1;
    //调整
    //root = maintain(root);
    //return root;
    return maintain(root);
}


void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}
//前序遍历
void output(Node *root) {
    if(root == NIL) return ;
    printf("(%d, %d, %d)\n", root->key, root->lchild->key, root->rchild->key);
    output(root->lchild);
    output(root->rchild);
    return ;
}
//随机数插入
int main() {
    srand(time(0));
    Node *root = NIL;
    for (int i = 1; i <= 5; i++) {
        root = insert(root, i);
        output(root);
        printf("-----------------\n"); 
    }
    return 0;
}
/*
//手动插入
int main() {
    Node *root = NIL;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++ ) {
        int key;
        scanf("%d", &key);
        root = insert(root, key);
        output(root);
        printf("-------------\n");
    }
    return 0;
}
*/
