/*************************************************************************
	> File Name: string_trie.c
	> Author: 
	> Mail: 
	> Created Time: Sun 30 Dec 2018 08:38:41 PM CST
 ************************************************************************/
//字典树

#include <stdio.h>
#include <stdlib.h>
#define BASE_CNT 26
#define BASE 'a'

typedef struct Node {
    int flag;//判断是否独立成词
    struct Node *next[BASE_CNT];
} Node;

Node *getNewNode() {
    Node *p = (Node *)malloc(sizeof(Node));
    for (int i = 0; i < BASE_CNT; i++) {
        p->next[i] = NULL;
    }
    p->flag = 0;
    return p;
}

void insert(Node *node, const char *str) {
    Node *p = node;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - BASE] == NULL) {
            p->next[str[i] - BASE] = getNewNode();
        }
        p = p->next[str[i] - BASE];
    }
    p->flag = 1;
    return ;
}

int search(Node *node, const char *str) {
    Node *p = node;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - BASE] == NULL) {
            return 0;
        }
        p = p->next[str[i] - BASE];
    }
    return p->flag;
}
void output(Node *node) {
    if (node == NULL) return ;
    Node *p = node;
    for (int i = 0; p->next[i]; i++) {
        printf("%s", p->next[i]);
    }
    printf("\n");
}
void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < BASE_CNT; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}

int main() {
    Node *root = getNewNode();
    char str[100];
    int op;
    while (scanf("%d%s", &op, str) != EOF) {
        switch (op) {
            case 1: {
                printf("insert %s to trie\n", str);
                insert(root, str);
                output(root);
            } break;
            case 2: {
                printf("search %s from trie = %d\n", str, search(root, str));
            } break;
        }
    }
    return 0;
}

