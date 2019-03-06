/*************************************************************************
	> File Name: string_kmp+.c
	> Author: 
	> Mail: 
	> Created Time: Wed 06 Mar 2019 10:28:12 AM CST
 ************************************************************************/
//kmp优化版
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
    printf("KMP(%s, %s) = %d\n",str1, "wor", KMP(str1, "wor", &con));
    printf("KMP search cnt: %d\n", con);

    return 0;
}
