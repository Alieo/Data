/*************************************************************************
	> File Name: string_kmp.c
	> Author: 
	> Mail: 
	> Created Time: Wed 06 Mar 2019 10:18:12 AM CST
 ************************************************************************/
//kmp算法
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
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
int main() {
    char str1[] = "hello world";
    printf("KMP(%s, %s) = %d\n",str1, "wor", KMP(str1, "wor"));
    return 0;
}
