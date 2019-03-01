/*************************************************************************
	> File Name: stack_ni.c
	> Author: 
	> Mail: 
	> Created Time: Sun 13 Jan 2019 02:15:35 PM CST
 ************************************************************************/
/*逆波兰式*/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int getNum(char *str, int *ret) {
    int i = 0, num = 0;
    while (str[i] <= '9' && str[i] >= '0') {
        num = num * 10 + str[i++] - '0';
    }
    *ret = num;
    return i;
}

int getTerm(char *str, int *ret) {
    int i = 0, temp;
    if (str[i] == 0) {
        return 0;
    }
    i += getNum(str + i, ret);
    if (str[i] == 0) {
        return i;
    }
    while (str[i]) {
        switch (str[i]) {
            case '*' : {
                //循环递归处理连*的情况
                i += getNum(str + i + 1, &temp) + 1;
                *ret *= temp;
                return i;
            } break;
            case '/' : {
                i += getNum(str + i + 1, &temp) + 1;
                *ret /= temp;
                return i;
            }
            default : return i;
        }
    }
    return i;
}

//给一个表达式，饼计算表达式的值
int calc(char *str) {
    int i = 0, a, b;
    char op;
    
    if (str[i] == 0) {
        return 0;
    }
    i += getTerm(str + i, &a);
    if (str[i] == 0) {
        return a;
    }
    while (str[i])  {
        op = str[i];
        //讲*/法当做一项，getTerm是处理*/的
        i += getTerm(str + i + 1, &b) + 1;
        switch (op) {
            case '+' : a += b; break; 
            case '-' : a -= b; break;
        }      
    }
    return a;
}

int main() {
    char str[1000];
    scanf("%s", str);
    printf("%d\n", calc(str));
    return 0;
}

