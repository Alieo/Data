/*************************************************************************
	> File Name: search_haxi.c
	> Author: 
	> Mail: 
	> Created Time: Tue 06 Nov 2018 07:55:09 PM CST
 ************************************************************************/
 //解决冲突: 拉链法
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Node {
    char *str;
    struct Node *next;
} Node;
//每个位置存的是链表
typedef struct Hash {
    Node **data;
    int size;
} Hash;
//头插法
//传入原先链表的头地址
Node *init_node(char *str, Node *head) {
    Node *p = (Node *)malloc(sizeof(Node));
    //strdup创建一片新的存储空间,将str拷贝到里面,最终返回新的存储空间的地址 
    p->str = strdup(str);
    p->next = head;
    return p;
}
Hash *init_hash(int n) {
    Hash *h = (Hash *)malloc(sizeof(Hash));
    h->size = n << 1;
    h->data = (Node **)calloc(sizeof(Node *), h->size);
    return h;
}

/*
 *查找: APHash  ZobristHash
 问题: 为何seed是31, 不是2
* */
int BKDRHash (char *str) {
    int seed = 31, hash = 0;
    for (int i = 0; str[i]; i++) hash = hash * seed + str[i];
    //为了保证最后返回的是一个正值, 所以&0x7fffffff
    return hash & 0x7fffffff;
}

int myhash(char *str) {
    int hash = 0;
    for (int i = 0; str[i]; i++) {
        hash += str[i] ^ 31 + 1;
    }
    return hash;
}


//拉链法
int insert(Hash *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    h->data[ind] = init_node(str, h->data[ind]);
    return 1;
}
//开放定址法
/*
int insert(Hash *h, char *str) {
    //BKDRhash
    int hash = get_hash_value(str);
    int ind = hash % h->size;
    Node *node = init_node(str, NULL);
    int times  = 0;
    while (h->data[ind]) {
        times++;
        //二次试探法
        ind += times * times;
        ind %= h->size;
    }
    h->data[ind] = node;
    return 1;
} 
*/
int search(Hash *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    Node *p = h->data[ind];
    while (p && strcmp(p->str, str)) p = p->next; 
    return p != NULL;
}

void clear_node(Node *n) {
    if (n == NULL) return ;
    Node *p = n, *q;
    while (p) {
        q = p->next;
        free(p->str);
        free(p);
        p = q;
    }
    return ;
}
void clear_hash(Hash *h) {
    if (h == NULL) return ;
    for (int i = 0 ;i < h->size; i++ ) {
        clear_node(h->data[i]);
    }
    free(h->data);
    free(h);
    return ;
} 


int main() {
    int op;
    char str[100];
    Hash *h = init_hash(100);
    while (scanf("%d%s", &op, str) != EOF) {
        switch (op) {
            case 0: {
                printf("insert %s to hash table\n", str);
                insert(h, str);
            } break;
            case 1: {
                printf("search %s result = %d\n", str, search(h, str));
            } break;
        }
    }
    return 0;
}
