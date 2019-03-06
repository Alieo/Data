/*************************************************************************
	> File Name: string_shift.c
	> Author: 
	> Mail: 
	> Created Time: Fri 04 Jan 2019 11:01:18 AM CST
 ************************************************************************/
//字符串匹配算法之shift-and算法
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEST(func, a, b) { \
    printf("%s(\"%s\", \"%s\") = %d\n", #func, a, b, func(a, b)); \
}
int ShiftAnd(char *str, char *pattern) {
    #define BASE 128
    int code[BASE] = {0}, len = 0;
    for (len = 0; pattern[len]; len++) {
        //将模式串各个字符出现的位置转为二进制。。
        code[pattern[len]] |= (1 << len);
    }
    int p = 0;
    for (int i = 0; str[i]; i++) {
        p = (p << 1 | 1) & code[str[i]];
        if (p & (1 << (len - 1))) return i - len + 1;
    }
    return -1;
    #undef BASE
}
int main() {
    char str[100], pattern[30];
    while (scanf("%s%s", str, pattern) != EOF) {
        TEST(ShiftAnd, str, pattern);
    }
    return 0;
}
