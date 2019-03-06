/*************************************************************************
	> File Name: string_shift.c
	> Author: 
	> Mail: 
	> Created Time: Fri 04 Jan 2019 11:01:18 AM CST
 ************************************************************************/
//字符串匹配算法之shift-and算法
#include<stdio.h>
#include <string.h>
int shift(char *str, char *pat) {
    int code[120] = {0}, len = 0;
    for (len = 0; pat[len]; len++) {
        //将模式串各个字符出现的位置转为二进制。。
        code[pat[len]] |= (1 << len);
    }
    int p = 0;
    for (int i = 0; str[i]; i++) {
        p = (p << 1) | 1 & code[str[i]];
        printf("%d\n", p);
        if (p & (1 << (len - 1))) return i - len + 1;
    }
    return -1;
}

int main() {
    char str[100] = "aebacbaer";
    char pat[100] = "acb";
    shift(str, pat);
    return 0;
}
