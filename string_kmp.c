/*************************************************************************
	> File Name: string.c
	> Author: 
	> Mail: 
	> Created Time: Thu 27 Dec 2018 10:25:57 PM CST
 ************************************************************************/
//KMP匹配
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//暴力
int BF(const char *text, const char *pat, int *p_con) {
    #define con (*p_con)
    int len1 = strlen(text);
    int len2 = strlen(pat);
    for (int i = 0; i < len1 - len2 + 1; i++, con++) {
        int flag = 1;
        for (int j = 0; pat[j] && flag; j++, con++) {
            if (text[i + j] == pat[j]) continue;
            flag = 0;
        }
        if (flag) return 1;
    }
    #undef con
    return 0;
}
/*
//未优化
int KMP(const char *text, const char *pat) {
    int len1 = strlen(text);
    int len2 = strlen(pat);
    int *next = (int *)malloc(sizeof(int) * len2);
    next[0] = -1;
    for (int i = 1; i < len2; i++) {
        int j = next[i - 1] + 1;
        while (j != -1 && pat[j + 1] != pat[i]) j = next[j];
        if (pat[j + 1] == pat[i])  {
            next[i] = j + 1;
        } else {
            next[i] = j;
        }
    }
    int j = -1;
    for (int i = 0; text[i]; i++) {
        while (j != -1 && pat[j + 1] != text[i]) j = next[j];
        if (pat[j + 1] == text[i]) j += 1;
        if (pat[j + 1] == 0) return 1;
    }
    return 0;
}
*/

//优化后
int KMP(const char *text, const char *pat, int *p_con) {
    #define con (*p_con)
    int len1 = strlen(text);
    int len2 = strlen(pat);
    int *next = (int *)malloc(sizeof(int) * len2);
    int j = -1;
    next[0] = -1;
    for (int i = 1; i < len2; i++, con++) {
        while (j != -1 && pat[j + 1] != pat[i]) j = next[j], con++;
        if (pat[j + 1] == pat[i])  {
            j += 1;
        } 
        next[i] = j;
    }
    j = -1;
    for (int i = 0; text[i]; i++, con++) {
        while (j != -1 && pat[j + 1] != text[i]) j = next[j], con++;
        if (pat[j + 1] == text[i]) j += 1;
        if (pat[j + 1] == 0) return 1;
    }
    #undef con
    return 0;
}

int main() {
    char str1[] = "hello world";
    int con = 0;
    printf("BF(%s, %s) = %d\n",str1, "wor", BF(str1, "wor", &con));
    printf("BF search cnt: %d\n", con);
    con = 0;
    printf("KMP(%s, %s) = %d\n",str1, "wor", KMP(str1, "wor", &con));
    printf("KMP search cnt: %d\n", con);

    return 0;
}
