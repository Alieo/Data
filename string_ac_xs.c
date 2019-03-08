/*************************************************************************
	> File Name: string_ac.c
	> Author: 
	> Mail: 
	> Created Time: Sun 13 Jan 2019 08:44:07 PM CST
 ************************************************************************/

//ac自动机线索化
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BASE 26
#define BEGIN_LETTER 'a'
#define MAX 200000
typedef struct Node {
    int flag;
    struct Node *next[BASE], *fail;
} Node;

typedef struct Queue {
    Node **data;
    int head, tail;
} Queue;

Queue *init_queue(int n) {
    Queue *q = (Queue *)calloc(sizeof(Queue), 1);
    q->data = (Node **)malloc(sizeof(Node *) * n);
    q->tail = q->head = 0;
    return q;
}

Node *front(Queue *q) {
    return q->data[q->head];
}

int empty(Queue *q) {
    return q->head == q->tail;
}

void push(Queue *q, Node *node) {
    q->data[q->tail++] = node;
    return ;
}

void pop(Queue *q) {
    if (empty(q)) return ;
    q->head++;
}

void clear_queue(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

Node *getNewNode() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    return p;
}

int insert(Node *root, const char *str) {
    int cnt = 0;
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - BEGIN_LETTER;
        if (p->next[ind] == NULL) p->next[ind] = getNewNode(), ++cnt;
        p = p->next[ind];
    }
    p->flag = 1;
    return cnt;
}

void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}
//线索化
void build_ac(Node *node, int n) {
    Node **queue = (Node **)malloc(sizeof(Node *) * (MAX + 5));
    int head = 0, tail = 0;
    queue[tail++] = node;
    while (head < tail) {
        //确定当前节点所有子节点的失败指针
        Node *now = queue[head++];
        for (int i = 0; i < BASE; i++) {
            if (now->next[i] == NULL) {
                if (now != node) now->next[i] = now->fail->next[i];
                continue;
            }
            Node *p = (now->fail ? now->fail->next[i] : node);
            /*
             //可去掉
            while (p && p->next[i] == NULL) p = p->fail;
            */
            if (p == NULL) p = node;
            now->next[i]->fail = p;
            queue[tail++] = now->next[i];
        }
        /*
         //可去掉
        Node *p = now->fail;
        for (int i = 0; i < BASE　&& now; i++) {
            if (now->next[i]) continue;
            now->next[i] = now->fail->next[i];
        }
        */
    }
    free(queue);
    return ;
}

int match(Node *root, const char *str) {
    /*
    int ret = 0;
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - BEGIN_LETTER;
    }
    */
    int cnt = 0;
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - BEGIN_LETTER;
        while (p && p->next[ind] == NULL) p = p->fail;
        if (p == NULL) p = root;
        else p = p->next[ind];
        Node *q = p;
        while (q) cnt += q->flag, q = q->fail;
    }
    return cnt;
}

int main() {
    Node *root = getNewNode();
    int n, cnt = 0;
    char str[1000];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        cnt += insert(root, str);
    }
    // build ac
    build_ac(root, cnt);
    scanf("%s", str);
    // match ac
    printf("match word cnt : %d\n", match(root, str));
    return 0;
}

