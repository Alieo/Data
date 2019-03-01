/*************************************************************************
> File Name: 表达式求值.cpp
> Author: 
> Mail: 
> Created Time: 2018年10月21日 星期日 15时37分31秒
************************************************************************/
//表达式求值(递归)
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#define INF 0x3f3f3f3f

int calc(const char *str, int l, int r) {
    int pos = -1, temp_prior = 0, prior = INF - 1;
    for (int i = l; i <= r; i++) {
        int cur_prior = INF;//最大值
        switch (str[i]) {
            
            case '(' : temp_prior += 100; break;
            case ')' : temp_prior -= 100; break;
            //
            case '+' : cur_prior = temp_prior + 1; break;
            case '-' : cur_prior = temp_prior + 1; break;
            case '*' : cur_prior = temp_prior + 2; break;
            case '/' : cur_prior = temp_prior + 2; break;
        }
        /*只要字符串中有运算符，cur_prior的值就会被改变.
         * 被改变后cur_prior值变小，就能取得该运算符的下标
        */
        if (cur_prior <= prior) {
            prior = cur_prior;
            //pos用来定位运算符所在的位置
            pos = i;
        }
    }
    /*如果pos == -1就意味着cur_prior的值没有被改变，
    * 所以pos值还是初始值，也就表示这i字符串中没有运算符，纯数字*/
    if (pos == -1) {
        //定义一个num来记录该纯数字，
        int num = 0;
        //while (j <= r && str[j] == ' ') ++j;
        for (int i = l; i <= r; i++) {
            if (str[i] < '0' || str[i] > '9') continue; 
            /*字符串转成数字，放在num中*/
            num = num * 10 + str[i] - '0';
        }
        return num;
    } 
    //不是纯数字，有运算符
    
    else {
        /*将运算符前面和运算符后边的数字剪出来，进行计算*/
        int a = calc(str, l, pos - 1);
        int b = calc(str, pos + 1, r);
        /* 计算形式: a + b  */
        switch (str[pos]) {
            case '+' : return a + b;
            case '-' : return a - b;
            case '*' : return a * b;
            case '/' : return a / b;
        }
    }
    return 0;
}

int main() {
    char str[1000];
    while (scanf("%[^\n]s", str) != EOF) {
        getchar();
        printf("%s = %d\n", str, calc(str, 0, strlen(str) - 1));
    }
    return 0;    
}
