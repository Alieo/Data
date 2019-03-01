/*************************************************************************
	> File Name: stack_exp.c
	> Author: 
	> Mail: 
	> Created Time: Fri 01 Mar 2019 02:40:17 PM CST
 ************************************************************************/
//表达式求值（双栈版）
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ERROR 0
#define OK 1

typedef struct Stack {
    int *data;
    int max_size, top_ind;
} Stack;

void init(Stack *s, int length) {
    s->data = (int *)malloc(sizeof(int) * length);
    s->top_ind = -1;
    s->max_size = length;
}

int push(Stack *s, int element) {
    if (s->top_ind >= s->max_size) return ERROR;
    s->top_ind++;
    s->data[s->top_ind] = element;
    return OK;
}

int pop(Stack *s) {
    if (s->top_ind < 0) return ERROR;
    s->top_ind--;
    return OK;
}

int top(Stack *s) {
    return s->data[s->top_ind];
}

int empty(Stack *s) {
    if (s->top_ind < 0) return 1;
    else return 0;
}

int precede(char op1, char op2/*比较符号优先级*/) {
    int a , b;
    if (op1 == '+' || op1 == '-') a = 1;
    else a = 2;
    if (op2 == '+' || op2 == '-') b = 1;
    else b = 2;
    return a > b;
}
int operate(char op, int a, int b/*计算...*/) {
    switch(op) {
        case '+': return a + b; 
        case '-': return b - a; 
        case '*': return a * b; 
        case '/': return b / a; 
    }
    return 0;
}
void calc(Stack *num, Stack *op) {
    /*num栈出两个数与op栈顶做运算*/
    int a = top(num);
    pop(num);
    int b = top(num);
    pop(num);
    push(num, operate(top(op), a, b));
    pop(op);
}

void clear(Stack *s) {
    free(s->data);
    free(s);
}

int main() {
     int n;
    Stack *num = (Stack *)malloc(sizeof(Stack));
    Stack *opr = (Stack *)malloc(sizeof(Stack));
    scanf("%d", &n);
    init(num, n);
    init(opr, n);
    char *buffer = (char *)malloc(sizeof(char) * (n + 1));
    scanf("%s", buffer);
    for (int i = 0; i < n; i++) {
        if (isdigit(buffer[i])) {
            push(num, buffer[i] - '0');
        } else {
            while (!empty(opr) && !precede(buffer[i], top(opr))) {
                calc(num, opr);
            }
            push(opr, buffer[i]);
        }
    }
    while (!empty(opr)) {
        calc(num, opr);
    }
    printf("%d\n", top(num));
    clear(num);
    clear(opr);
    free(buffer);
    return 0;
}
