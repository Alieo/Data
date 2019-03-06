/*************************************************************************
	> File Name: string_double.c
	> Author: 
	> Mail: 
	> Created Time: Sun 06 Jan 2019 03:15:31 PM CST
 ************************************************************************/
//双数组字典树
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    int flag;
    struct Node *next[26];
} Node;

typedef struct DATNode {
    /* base　存着第一个非空孩子节点的地址 */
    /* 孩子节点地址 = 根的base + i */
    /* check　存父节点地址 */
    int base, check;

} DATNode;


Node *getNewNode() {
    Node *p  = (Node *)malloc(sizeof(Node));
    p->flag = 0;
    return p;
}

int  insert(Node *node, const char *str) {
    Node *p = node;
    int cnt = 0;
    for (int i  =0 ; str[i]; i++) {
        if (p->next[str[i] - 'a'] == NULL) {
            p->next[str[i] - 'a'] = getNewNode();
            cnt += 1;
        }
        p = p->next[str[i] - 'a'];
    }
    p->flag = 1;
    return cnt;
}



void clear(Node *node) {
    if (node == NULL) return ;
    for (int i  = 0; i < 26; i++) {
        clear(node->next[i]);
    }
    free(node);
    return;
}

int getBase(Node *node, DATNode *trie) {
    int base = 1, flag = 0;
    while (!flag) {
        flag = 1;
        base += 1;
        for (int i = 0; i < 26; i++) {
            if (node->next[i] == NULL) {
                continue;
            }
            if (trie[base + i].check == 0) {
                continue;
            }
            flag = 0;
            break;
        }
    }
    return base;
}

void Transform(Node *node, DATNode *trie, int ind) {
    /* 如果独立成词，则转为负数 */
    if (node->flag) trie[ind].check = -trie[ind].check;
    trie[ind].base = getBase(node, trie);
    //printf("trie[%d].base = %d\n", ind, trie[ind].base);
 
    for (int i = 0; i < 26; i++) {
        if (node->next[i] == NULL) {
            continue;
        }
        trie[trie[ind].base + i].check = ind;
    }
    for (int i = 0; i < 26; i++) {
        if(node->next[i] == NULL) {
            continue;
        }
        Transform(node->next[i], trie, trie[ind].base + i);
    }

}
int search(DATNode *trie, const char *str) {
    int p = 1;
    for (int i = 0; str[i] ; i++) {
        int delta = str[i] - 'a';
        int check = abs(trie[trie[p].base + delta].check);
        if (check - p) return 0;
        p = trie[p].base + delta;
    }
    return (trie[p].check < 0);

}



int main() {
    int n , cnt = 1;
    char str[100];
    Node *root = getNewNode();
    scanf("%d", &n);
    while (n--) {
        scanf("%s", str);
        cnt += insert(root, str);
    }
    DATNode *trie = (DATNode *)calloc(sizeof(DATNode), cnt * 10);
    
    //转换
    Transform(root, trie, 1);
    while (scanf("%s", str) != EOF) {
        printf("search %s = %d\n", str, search(trie, str));
    }
    clear(root);
    return 0;
}
