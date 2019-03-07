/*************************************************************************
	> File Name: string_doublearr.c
	> Author: 
	> Mail: 
	> Created Time: Sun 06 Jan 2019 04:13:30 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAXNUM 170
/*使用双数组字典树：
    将string_doublearr.in的数字转化为相应的字母
*/
typedef struct Node {
    int base, check;
} Node;
Node trie[500];
void doub(int ind, int k, char *str) {
    if (trie[ind].check < 0) {
        printf("%s\n", str);
    }

    for (int i = 0; i < 26; i++) {
        //子节点的值是base的值 + i(0,1,2,3...)
        int check = abs(trie[trie[ind].base + i].check);
        if (check - ind == 0 && trie[ind].base + i != 1) {
            str[k] = 'a' + i;
            str[k + 1] = 0;
            doub(trie[ind].base + i, k + 1, str);
        }
    }
    return ;
}




int main() {
    int a, b, c;
    while (scanf("%d%d%d", &a, &b, &c) != EOF) {
        trie[a].base = b;
        trie[a].check = c;
    }
    char str[100];
    doub(1, 0, str);    
    return 0;
}
