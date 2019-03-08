/*************************************************************************
    > File Name: BST.c
    > Author: 
    > Mail: 
    > Created Time: Sun 02 Dec 2018 08:17:11 PM CST
 ************************************************************************/
//二叉排序树
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct BSTNode {
    int key;
    struct BSTNode *lchild, *rchild;
} BSTNode;
BSTNode *init(int key) {
    BSTNode *p = (BSTNode *)malloc(sizeof(BSTNode));
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}

BSTNode *insert(BSTNode *root, int key) {
    if (root == NULL) return init(key);
    if (root->key == key) return root;
    if (key < root->key) {
        root->lchild = insert(root->lchild, key);
    } else root->rchild = insert(root->rchild, key);
    return root;
}
BSTNode *pre(BSTNode *node) {
    BSTNode *temp = node->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp;
}

BSTNode *erase(BSTNode *root, int key) {
    if (root == NULL) return root;
    if (root->key == key) {
        //度 = 0;
        if (root->lchild == NULL && root->rchild == NULL) {
            printf("delete 0\n");
            free(root); 
            return  NULL;
        }
        //度 = 2;
        else if (root->lchild != NULL && root->rchild != NULL){
            printf("delete 2\n");
            BSTNode *temp = pre(root);
            temp->key ^= root->key;
            root->key ^= temp->key;
            temp->key ^= root->key;
            root->lchild = erase(root->lchild, key);
        } 
        //度 = 1;
        else {            
            printf("delete 1\n");
            BSTNode *temp = root->lchild != NULL ? root->lchild : root->rchild;
            free(root);
            return temp;
        }
    } else {
        if (root->key < key) root->rchild = erase(root->rchild, key);
        else root->lchild = erase(root->lchild, key);
    }
    return root;
}
void output(BSTNode *root) {
    if (root == NULL) return  ;
    output(root->lchild);
    printf("%d ", root->key);
    output(root->rchild);
    return ;
}
//比较大小, 传参要将大数放前面
int cmp(int a, int b) {
    if (a > b) return 1;
    return 0;
}
//给你一棵树, 判断这棵树是不是二叉排序树
int judge(BSTNode *root) {
    if (root == NULL) return 1;
    if (root->lchild != NULL) {
        if (!cmp(root->key, root->lchild->key)) return 0;
        if (!judge(root->lchild)) return 0;
    }
    if (root->rchild != NULL) {
        if (!cmp(root->rchild->key, root->key)) return 0;
        return judge(root->rchild);
    }
    return 1;
}
void clear(BSTNode *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}
int main() {
    srand (time(0));
    while (1) {
        BSTNode *root = NULL;
        #define OP_NUM 20
        for (int i = 0; i < OP_NUM; i++) {
            int key = rand() % 30;
            root = insert(root, key);
            printf("insert [%d] to tree\n", key);
            //__output(root), printf("\n");
            output(root), printf("\n");
        }
        for (int i = 0; i < OP_NUM; i++) {
            int key2 = rand() % 30;
            root = erase(root, key2);
            printf("delete [%d] from tree\n", key2);
            output(root), printf("\n");
        }
        if (judge(root)) printf("this tree is BSTree\n");
        else {
            printf("this tree is not BSTree\n");
            getchar();
        }
        clear(root);
        printf("\n\n\n");
    }
    return 0;
}
