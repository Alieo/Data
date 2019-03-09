/*************************************************************************
	> File Name: tree_rb1.c
	> Author: 
	> Mail: 
	> Created Time: Sun 17 Feb 2019 10:08:05 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define RED 0
#define BLACK 1
#define DOUBLE_BLACK 2

typedef struct Node {
    int key, color;
    struct Node *lchild, *rchild;
} Node;

Node *NIL;

Node *init(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->color = RED;
    p->lchild = p->rchild = NIL;
    return p;
}
__attribute__((constructor))
void init_NIL() {
    NIL = init(-1);
    NIL->color = BLACK;
    NIL->lchild = NIL->rchild = NIL;
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}

int has_red_child(Node *root) {
    return root->lchild->color == RED || root->rchild->color == RED;
}

Node *insert_maintain(Node *root) {
    if (!has_red_child(root)) return root;
    if (root->lchild->color == RED && root->rchild->color == RED) {
        if (!has_red_child(root->lchild) && !has_red_child(root->rchild)) {
            return root;
        }
    }
    //root左孩子为红色，且左孩子的孩子有红色    
    else if (root->lchild->color == RED && has_red_child(root->lchild)) {
        if (root->lchild->rchild->color == RED) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    }
    //root右孩子为红色，且右孩子的孩子有红色
    else if (root->rchild->color == RED && has_red_child(root->rchild)) {
        if (root->rchild->lchild->color == RED) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    else return root;
    //红色上顶
    root->color = RED;
    root->lchild->color = root->rchild->color = BLACK;
    return root;
}

Node *__insert(Node *root, int key) {
    if (root == NIL) return init(key);
    if (key == root->key) return root;
    else if (key < root->key) {
        root->lchild = __insert(root->lchild, key);
    }
    else {
        root->rchild = __insert(root->rchild, key);
    }
    return insert_maintain(root);
}

Node *insert(Node *root, int key) {
    root = __insert(root, key);
    root->color = BLACK;
    return root;
}

Node *erase_maintain(Node *root) {
    if (root->lchild->color != DOUBLE_BLACK && root->rchild->color != DOUBLE_BLACK) return root;
    //当兄弟颜色为黑色，且兄弟孩子也为黑色
    #define UNBALANCE(a, b) root->a->color == DOUBLE_BLACK && root->b->color == BLACK && !has_red_child(root->b)
    if (UNBALANCE(lchild, rchild) || UNBALANCE(rchild, lchild)) {
        root->color += 1;
        root->lchild->color -= 1;
        root->rchild->color -= 1;
        return root;
    }
    #undef UNBALANCE
    
    //当root左孩子是双重黑
    if (root->lchild->color == DOUBLE_BLACK) {
        //兄弟是红色
        if (root->rchild->color == RED) {
            root = left_rotate(root);
            root->color = BLACK;
            root->lchild->color = RED;
            root->lchild = erase_maintain(root->lchild);
            return root;
        }
        
        root->lchild->color -= 1;    
        //当兄弟是黑色，且兄弟的左孩子是红色
        if (root->rchild->rchild->color != RED) {
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = BLACK;
            root->rchild->rchild->color = RED;
        }
        root = left_rotate(root);
        root->color = root->lchild->color;
    }
    //当root右孩子是双重黑
    else {
        if (root->lchild->color == RED) {
            root = right_rotate(root);
            root->color = BLACK;
            root->rchild->color = RED;
            root->rchild = erase_maintain(root->rchild);
            return root;
        }
        root->rchild->color -= 1;    
        if (root->lchild->lchild->color != RED) {
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = BLACK;
            root->lchild->lchild->color = RED;
        }
        root = right_rotate(root);
        root->color = root->rchild->color;
    }
    root->lchild->color = root->rchild->color = BLACK;
    return root;
}

Node *pre(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

Node *__erase(Node *root, int key) {
    if (root == NIL) return root;
    if (key == root->key) {
        //度＝0, 1
        if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = (root->lchild != NIL ? root->lchild : root->rchild);
            temp->color += root->color;
            free(root);
            return temp;
        }        
        //度＝2
        //１．找出该节点的前驱
        //２．该节点的key值将被其前驱的key值所覆盖
        //３．此时问题变成了删除当前root左子树中某个度为0,1的节点
        else {
            Node *temp = pre(root);
            root->key = temp->key;
            root->lchild = __erase(root->lchild, temp->key);
        }
    } else if (key < root->key) {
        root->lchild = __erase(root->lchild, key);
    } else root->rchild = __erase(root->rchild, key);
    return erase_maintain(root);
}

Node *erase(Node *root, int key) {
    root = __erase(root, key);
    root->color = BLACK;
    return root;
}

void output(Node *root) {
    if (root == NIL) return ;
    printf("(%d %d %d) = %d\n", root->key, root->lchild->key, root->rchild->key, root->color);
    output(root->lchild);
    output(root->rchild);
    return ;
}


void clear(Node *root) {
    if (root == NIL) return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}
int main() {
    int a, b;
    Node *root = NIL;
    while (scanf("%d %d", &a, &b) != EOF) {
        switch (a) {
            case 1:{
                root = insert(root, b);
            } break;
            case 2: {
                root = erase(root, b);
            } break;
            case 3: {
                output(root);
            } break;
        }
    }
    clear(root);
    return 0;
}
