/*************************************************************************
	> File Name: stack.c
	> Author: 
	> Mail: 
	> Created Time: 2018年10月22日 星期一 21时01分54秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
typedef struct Stack {
    int *data;
    int top, size;
} Stack;
Stack *init(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * n);
    s->top = -1;
    s->size = n;
    return s;
}
int empty(Stack *s) {
    return s->top == -1;
}
int top(Stack *s) {
    if (empty(s)) return 0;
    return s->data[s->top];
}
int push(Stack *s, int value) {
    if (s->top + 1 == s->size) return 0;
    s->top += 1;
    s->data[s->top] = value;
    return 1;
}
void pop(Stack *s) {
    if (empty(s)) return ;
    s->top -= 1;
    return ;
}
void clear(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;

}
void output(Stack *s) {
    printf("Stack = [");
    for (int i = s->top; i >= 0; i--) {
        printf(" %d", s->data[i]);
        i && printf(",");
    }
    printf("]\n");
    return ;
    
}
int main() {
    //输入n, m
    //如果n == 1, 入站
    //如果n == 0，出站，栈顶出站
    int max = 5;
    Stack *s = init(max);
    int n, m;
    while (max--) {
        scanf("%d %d", &n, &m);
        if (n == 1) push(s, m);
        else if (n == 0) pop(s);
    }
    output(s);
    clear(s);
    return 0;
}
