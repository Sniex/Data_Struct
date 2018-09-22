/*************************************************************************
	> File Name: raddix_sort.cpp
	> Author: Yu_dong
	> Mail: 1124250973@qq.com
	> Created Time: 2018年07月28日 星期六 11时48分57秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define lowbit(x) (x & 0xffff)
#define highbit(x) ((x >> 16) & 0xffff)
#define TEST(n, func) { \
    int num[n] = {0}; \
    printf("["); \
    for (int i = 0; i < n; i++) { \
        num[i] = rand() % 1000000; \
        printf("%d ", num[i]); \
    } \
    printf("]\n"); \
    func; \
    output(num, n, #func); \
}


void raddix_sort(int *num, int n);
void output(int *num, int n, const char *str) {
    printf("%s = [", str);
    for (int i = 0; i < n; i++) {
        printf("%d ", num[i]);
    }
    printf("]\n");
}


int main() {
    srand(time(0));
    TEST(20, raddix_sort(num, 20));
    return 0;
}

void raddix_sort(int *num, int n) {
    #define MAX_N 65536
    int *temp = (int *)malloc(sizeof(int) * n);
    int cnt[MAX_N] = {0};
    for (int i = 0; i < n; i++) cnt[lowbit(num[i])]++;
    for (int i = 1; i < MAX_N; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) 
        temp[--cnt[lowbit(num[i])]] = num[i];

    for (int i = 0; i < n; i ++) cnt[highbit(temp[i])]++;
    for (int i = 1; i < MAX_N; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) 
        temp[--cnt[highbit(temp[i])]] = temp[i];
    // free(temp);
    #undef MAX_N
}
