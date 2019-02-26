/*************************************************************************
	> File Name: dui_sort.c
	> Author: 
	> Mail: 
	> Created Time: 2018年10月30日 星期二 20时27分29秒
 ************************************************************************/
//堆排序
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#define swap(a, b) {\
    __typeof(a) __temp = a; a = b; b = __temp;\
}


void heap_sort(int *arr, int n) {
    int *p = arr - 1;//指向数组前一位
    for (int i = 2; i <= n; i++) {
        //新进入堆里的元素是p[i]
        int ind = i;
        while(ind > 1) {
            if (p[ind] <= p[ind >> 1]) break;
            swap(p[ind], p[ind >> 1]);
            ind >>= 1;
        }
    }
    //建好堆了
    for (int i = n ; i > 1; i--) {
        swap(p[i], p[1]);
        int ind = 1;
        while ((ind << 1) <= i - 1) {
            int temp = ind;
            if (p[temp] < p[ind << 1]) temp = ind << 1;
            if ((ind << 1 | 1) <= i - 1 && p[temp] < p[ind << 1 | 1]) temp = ind << 1 | 1;
            if (temp == ind) break;
            swap(p[temp], p[ind]);
            ind = temp;
        }
    }
    return ;
}

void output(int *num, int n) {
    printf("arr = [");
    for (int i = 0; i < n; i++) {
        printf(" %d", num[i] );
        i == n - 1 || printf(",");
    }
    printf("]\n");
}

int main() {
    #define MAX 20
    int arr[MAX];
    for (int i = 0; i< MAX; i++) arr[i] = rand()% 100;
    output(arr, MAX);
    heap_sort(arr, MAX);
    output(arr, MAX);
    return 0;
}
