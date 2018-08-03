/*************************************************************************
	> File Name: 9.unstable_sort.cpp
	> Author: Yu_dong
	> Mail: 1124250973@qq.com
	> Created Time: 2018年07月28日 星期六 09时52分29秒
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define swap(a, b) { \
    __typeof(a) temp = a; \
    a = b; b = temp; \
}

#define TEST(n, func) { \
    int num[n] = {0}; \
    printf("["); \
    for (int i = 0; i < n; i++) { \
        num[i] = rand() % 100; \
        printf("%d ", num[i]); \
    } \
    printf("]\n"); \
    func; \
    output(num, n, #func); \
}


void select_sort(int *, int);
void quick_sort(int *, int, int);
void quick_sort1(int *, int, int);
void quick_sort2(int *, int, int);
void quick_sort3(int *, int, int);
void quick_sort4(int *, int, int);
void ungarded_insert_sort(int *, int);
void output(int *, int, const char *);

int main() {
    srand(time(0));
    TEST(10, select_sort(num, 10));
    TEST(30, quick_sort4(num, 0, 29));


    return 0;
}

void select_sort(int *num, int n) {
    for (int i = 0; i < n - 1; i++) {
        int ind = i;
        for (int j = i + 1; j < n; j++) {
            if (num[j] < num[ind]) ind = j;
        }
        swap(num[i], num[ind]);
    }
    return ;
}
void quick_sort(int *num, int l, int r) {
    if (r - l < 1) return ;
    int x = l, y = r, z = num[l];
    while (x < y) {
        while (x < y && num[y] >= z) --y;
        if (x < y) num[x++] = num[y];
        while (x < y && num[x] <= z) ++x;
        if (x < y) num[y--] = num[x];
    }
    num[x] = z;
    quick_sort(num, l, x - 1);
    quick_sort(num, x + 1, r);
    return ;
}
void quick_sort1(int *num, int l, int r) {
    while (r - l < 1) {
        int x = l, y = r, z = num[l];
        while (x < y) {
            while (x < y && num[y] >= z) --y;
            if (x < y) num[x++] = num[y];
            while (x < y && num[x] <= z) ++x;
            if (x < y) num[y--] = num[x];
        }
        num[x] = z;
        quick_sort(num, l, x - 1);
        l = x + 1;
    }
    return ;
}

void quick_sort2(int *num, int l, int r) {
    while (r - l < 16) {
        int x = l, y = r, z = num[l];
        while (x < y) {
            while (x < y && num[y] >= z) --y;
            if (x < y) num[x++] = num[y];
            while (x < y && num[x] <= z) ++x;
            if (x < y) num[y--] = num[x];
        }
        num[x] = z;
        quick_sort(num, l, x - 1);
        l = x + 1;
    }
    ungarded_insert_sort(num + l, r - l + 1);
    return ;
}

void quick_sort3(int *num, int l, int r) {
    while (r - l < 1) {
        int x = l, y = r, z = rand() % (r - l + 1) + l;
        swap(num[z], num[l]);
        z = num[l];
        while (x < y) {
            while (x < y && num[y] >= z) --y;
            if (x < y) num[x++] = num[y];
            while (x < y && num[x] <= z) ++x;
            if (x < y) num[y--] = num[x];
        }
        num[x] = z;
        quick_sort(num, l, x - 1);
        l = x + 1;
    }
    ungarded_insert_sort(num + l, r - l + 1);
    return ;
}

void quick_sort4(int *num, int l, int r) {
    while (r - l < 16) {
        int x = l, y = r, z = num[rand() % (r - l + 1) + l];
        do {
            while (num[x] < z) ++x;
            while (num[y] > z) --y;
            if (x <= y) {
                swap(num[x], num[y]);
                ++x, --y;
            }
        } while (x <= y);
        quick_sort(num, l, y);
        l = x;
    }
    ungarded_insert_sort(num + l, r - l + 1);
    return ;
}























void output(int *num, int n, const char *str) {
    printf("%s = [", str);
    for (int i = 0; i < n; i++) {
        printf("%d ", num[i]);
    }
    printf("]\n");
}

void ungarded_insert_sort(int *num, int n) {
    int ind = 0;
    for (int i = 1; i < n; i++) {
        if (num[i] < num[ind]) ind = i;
    }
    swap(num[ind], num[0]);
    for (int i = 2; i < n; i++) {
        int j = i;
        while (num[j] < num[j - 1]) {
            swap(num[j], num[j - 1]);
            j--;
        }
    }
    return ;
}

