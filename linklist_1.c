/*************************************************************************
	> File Name: linklist_1.c
	> Author: 
	> Mail: 
	> Created Time: Fri 16 Nov 2018 02:46:15 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//type = int*;
typedef struct LinkNode {
    int data;
    struct LinkNode *next;
} LinkNode, *LinkList;

//LinkList = struct LinkNode*;

LinkNode *getnewnode(int val) {
    LinkNode *p  = (LinkNode *)malloc(sizeof(LinkNode));
    p->data = val;
    p->next = NULL;
    return p;
}

LinkNode *insert(LinkList l, int val, int ind) {
    LinkNode ret, *p = &ret;
    ret.next = l;
    while (ind--) {
        p = p->next;
        if (p == NULL) return l;
    }
    LinkNode *new_node = getnewnode(val);
    new_node->next = p->next;
    p->next = new_node;
    return ret.next;
}
LinkNode *erase(LinkList l, int ind) {
    LinkNode ret, *p = &ret;
    ret.next = l;
    while (ind--) {
        p = p->next;
        if (p == NULL) return l;
    }
    if (p->next == NULL) return l;
    LinkNode *q = p->next;
    p->next = p->next->next;
    free(q);
    return ret.next;
}
void clear(LinkList head) {
    if (head == NULL) return ;
    LinkNode *p = head, *q;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
}
void output(LinkList l) {
    LinkNode *p = l;
    while (p != NULL) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("NULL\n");
    return;
}
int main() {
    srand(time(0));
    LinkList l = NULL;
    int length = 0;
    #define MAX_OP 20
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 4, value, ind;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                ind = rand() % (length + 1);
                value = rand() % 100;
                printf("insert(%d, %d) to LinkList\n", value, ind);
                l = insert(l , value, ind);
                output(l);
                length += 1;
            } break;
            case 3: {
                if (length == 0) break;
                ind = rand() % length;
                printf("erase(%d) from LinkList\n", ind);
                l = erase(l, ind);
                output(l);
                length -= 1;
            } break;
        }
    }
    clear(l);
    return 0;
}
