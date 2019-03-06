/*************************************************************************
	> File Name: string_sunday.c
	> Author: 
	> Mail: 
	> Created Time: Fri 04 Jan 2019 10:13:44 AM CST
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEST(func, a, b) { \
    printf("%s(\"%s\", \"%s\") = %d\n", #func, a, b, func(a, b)); \
}

int Sunday(char *str, char *pattern) {
    #define BASE 128
    int ind[BASE] = {0};
    int len = strlen(pattern), max_len = strlen(str);
    for (int i = 0; i < BASE; i++) {
        ind[i] = len + 1;
    }
    for (int i = 0; i < len; i++) {
        ind[pattern[i]] = len - i;
    }
    for (int i = 0; i < max_len;){
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
    #undef BASE
}
int main() {
    char str[100], pattern[30];
    while (scanf("%s%s", str, pattern) != EOF) {
        TEST(Sunday, str, pattern);
    }
    return 0;
}
