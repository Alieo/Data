/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2018年10月11日 星期四 19时00分14秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define DEFAULT_ARG(a, b) ((#a)[0] ? a + 0: b)
#define init(a) __init(DEFAULT_ARG(a, 10)) 

typedef struct Vector{
    int *data;
    int size, length;
} Vector;

Vector *__init(int n) {
    Vector *p = (Vector *)malloc(sizeof(Vector));
    p->data = (int *)malloc(sizeof(int) * n);
    p->size = n;
    p->length = 0;
    return p;
}

//扩容
int expand(Vector *v) {
    int *p = (int *)realloc(v->data, sizeof(int) * 2 * v->size);
    //重新申请内存空间, 第一项是原空间的地址,第二是新申请的空间大小
    /*如果当前的存储空间不够用, 他优先看看表后面能不能扩容, 
     * 能扩就在原来的表后扩, 不能扩就重新开辟一片空间, 
     * 将原始数据copy到新申请的空间里,并自动进行释放旧空间, 
     * 第三种情况, 如果表后扩容失败,重新申请也失败, 
     * 则realloc返回一个空地址, 这个时候就发生了内存泄漏. 
* 内存泄露: 是指自己申请的一个地址返回空,
    * 并且把旧的指向原数据的地址覆盖掉了,
    * 那么这时返回的是一个指向空的地址,数据丢了
    * 解决空间泄露问题:
    *用一个临时指针p来指向realloc出来的空间,当p = NULL, return 0;当p不为空时才继续执行
    
    * */
    if (p == NULL) return 0;
    v->data = p;
    v->size *= 2;
    return 1;
}


int insert(Vector *v, int value, int ind) {
    if (v->length == v->size) {
        if (expand(v) == 0) {
            return 0;
        }    
    }
    if (ind < 0 || ind > v->length) return 0;
    for (int i = v->length - 1; i >= ind; --i) {
        v->data[i + 1] = v->data[i];
    }
    v->data[ind] = value;
    v->length += 1;
    return 1;
}

int erase(Vector *v, int ind) {
    if (v->length == 0) return 0;
    if (ind < 0 || ind >= v->length) return 0;
    for (int i = ind + 1; i < v->length; i++) {
        v->data[i - 1] = v->data[i];
    }
    v->length -= 1;
    return 1;
}

void clear(Vector *v) {
    if (v == NULL) return ;
    free(v->data);
    free(v);
    return ;
}


void output(Vector *v) {
    printf("Vector = [");
    for (int i = 0; i < v->length; i++) {
        printf(" %d", v->data[i]);

    }
    printf("]\n");
    return ;
}

int main() {
    Vector *v = init();
    #define MAX 40
    for (int t = 0 ; t < MAX; t++) {
        int op = rand()%5, ind, value;
        scanf("%d", &op);
        switch (op) {
            case 4:
            case 2:
            case 3:
            case 0: {
                ind = rand() % (v->length + 3) - 1;
                value = rand() % 100;
                printf("[%d] insert (%d, %d) to Vector\n",  insert(v, value, ind),value, ind);
                output(v);
            } break;
            case 1: {
                ind = rand() %(v->length + 3) - 1;
                printf("[%d] erase(%d) from Vector\n", erase(v, ind), ind);
                output(v);
            }break;
        }
    }
    clear(v);
    return 0;
}

int main() {
    Vector *v1 = init();
    Vector *v2 = init();
    int n, m;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int temp;
        scanf("%d", &temp);
        insert(v1, temp);
    }
    
    
    
    return 0;
}
