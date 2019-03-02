/*************************************************************************
	> File Name: stack_monot.c
	> Author: 
	> Mail: 
	> Created Time: Sat 15 Dec 2018 03:16:34 PM CST
 ************************************************************************/
/*
单调栈例题：

例题1：左右侧最近更大数的距离问题。 给一个数组，返回一个大小相同的数组。返回的数组的第i个位置的值应当是，对于原数组中的第i个元素，至少往右走多少步，才能遇到一个比自己大的元素（如果之后没有比自己大的元素，或者已经是最后一个元素，则在返回数组的对应位置放上-1）。

简单的例子：
input: 5,3,1,2,4
return: -1 3 1 1 -1 
* */
#include<stdio.h>
#include<stdlib.h>
typedef struct Stack {
    int *data;
    int top, size;
} Stack;
Stack *init(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int ) * n);
    s->top = -1;
    s->size = n;
    return s;
}
int empty(Stack *s) {
    return s->data[s->top] == -1;
}
int top(Stack *s) {
    if (empty(s)) return 0;
    return s->data[s->top];
}
void pop(Stack *s) {
    if (empty(s)) return ;
    s->top -= 1;
    return ;
}
void push(Stack *s, int value) {
    if (s->top + 1 == s->size) return ;
    while (value > s->data[s->top]) {
        pop(s); 
    } 
    s->top += 1;
    s->data[s->top] = value;
    return ;
}

void output(Stack *s) {
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->data[i]);
        i && printf(",");
    }
    return ;
}
void clear(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}
int main() {
    int n, a;
    scanf("%d", &n);
    Stack *s = init(n);
    while (n--) {
        scanf("%d", &a);
        push(s, a);
        output(s);
        int count = 0;
        while (s->top < a) {
            count += 1;
            pop(s);
            push(s, a);
        }
        if (count == 0) printf("-1 ");
        else printf("%d ", count + 1);
    }
    clear(s);
    return 0;
}
