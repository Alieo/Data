/*************************************************************************
	> File Name: search_efen.c
	> Author: 
	> Mail: 
	> Created Time: Tue 06 Nov 2018 07:26:13 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define P(func) { \
    printf("%s = %d\n", #func, func); \
}

//1 2 3 4 5
int efen1(int *num, int n, int x) {
    int head = 0, tail = n - 1, mid;
    while(head <= tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == x) return mid;
        if (num[mid] > x) tail = mid - 1;
        else head = mid + 1;
    }
    return -1;
}
//1111000
int efen2(int *data, int n) {
    int l = -1, r = n, mid;
    while (l < r) {
        mid = (l + r + 1) >> 1;
        if (data[mid] == 1) l = mid;
        else r = mid - 1;
    }
    return l;
}
//让efen2变死循环
/*
int _efen2(int *data, int n) {
    int l = -1, r = n - 1, mid;
    while (l < r) {
        mid = (l + r ) >> 1;
        if (data[mid] == 1) l = mid;
        else r = mid - 1;
    }
    return l;
}
*/
//000111

int efen3(int *data, int n) {
    int l = 0, r = n, mid;
    while (l < r) {
        mid = (l + r) >> 1;
        if (data[mid] == 1) r = mid;
        else l = mid + 1;
    }
    return l == n ? -1 : l; 
}
int main() {
    int arr1[10] = {1,3,5,7,11,13,17,19,23,29};
    int arr2[10] = {1,1,1,0,0,0,0,0,0,0};
    int arr3[10] = {0,0,0,0,0,0,1,1,1,1};
    //_efen2(arr1, 10);
    P(efen1(arr1, 10, 11));
    P(efen2(arr2, 10));
    P(efen3(arr3, 10));
    return 0;
}
