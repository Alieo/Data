/*************************************************************************
	> File Name: string_alg.c
	> Author: 
	> Mail: 
	> Created Time: Sun 30 Dec 2018 07:42:59 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define TEST(func, a, b) { \
    printf("%s(\"%s\", \"%s\") = %d\n", #func, a, b, func(a, b)); \
}

int BF(char *str, char *pattern) {
    for (int i = 0; str[i]; i++) {
        int flag = 1;
        for (int j = 0; pattern[j]; j++) {
            if (str[i + j] == pattern[j]) continue;
            flag = 0;
            break;
        }
        if (flag) return i;
    }
    return -1;
}
int KMP(char *str, char* pattern) {
    int *next = (int *)malloc(sizeof(int) * strlen(pattern));
    next[0] = -1;
    for (int i = 1; str[i]; i++) {
        int j = next[i - 1];
        while (j != -1 && pattern[j + 1] != pattern[i]) j = next[j];
        if (pattern[j + 1] == pattern[i]) next[i] = j + 1;
        else next[i] = -1;
    }
    int i = 0, j = -1;
    while (str[i]) {
        while (j != -1 && str[i] != pattern[j + 1]) j = next[j];
        if (str[i] == pattern[j + 1]) {
            j += 1;
        } 
        i += 1;  
        if (pattern[j + 1] == 0) return i - strlen(pattern);
    }
    return -1;
}

int Sunday(char *str, char *pattern) {
    #define Base 128
    int ind[Base] = {0};
    int len = strlen(pattern);
    for (int i = 0; i < Base; i++) {
        ind[i] = len + 1;
    }
    for (int i = 0; i < len; i ++) {
        ind[pattern[i]] = len - i;
    }
    for (int i = 0; i < strlen(str);) {
        int flag = 1;
        for (int j = 0; j < len; j++) {
            if (str[i + j] == pattern[j]) continue;
            i += ind[str[i + len]];
            flag = 0;
            break;
        }
        if (flag) return i;
    }
    return -1;
    #undef Base
}
int Shiftand(char *str, char *pattern) {
   #define BASE 128
    int code[BASE] = {0}, len = 0;
    for (len = 0; pattern[len]; len++) {
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
        TEST(BF, str, pattern);
        TEST(KMP, str,pattern);
        TEST(Sunday, str, pattern);
        TEST(Shiftand, str,pattern);
    }
    return 0;
}
