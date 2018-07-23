/*************************************************************************
	> File Name: 1.vector.cpp
	> Author: Yu_dong
	> Mail: 1124250973@qq.com
	> Created Time: 2018年06月04日 星期一 19时57分49秒
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define malloc2(size) my_malloc(size, __FILE__, __func__, __LINE__)

void *my_malloc(int size, const char *file, const char *func, int line_no) {
    void *data = malloc(size);
    if (data == NULL) {
        fprintf(stderr, "[%s : %s-> %d] malloc error\n", file, func, line_no);
        fflush(stderr);
        exit(-1);
    }
    return data;
}

typedef struct Vector {
    int *data;
    int size, length;
} Vector;

Vector *init() {
    static int64_t n = 10000000000000000LL;
    Vector *p = (Vector *)malloc2(sizeof(Vector));
    p->data = (int *)malloc2(sizeof(int) * n);
    p->size = n;
    p->length = 0;
    return p;
}

int expand(Vector *v) {
    int new_size = v->size;
    int *data;
    while (new_size) {
        data = (int *)realloc(v->data, sizeof(int) * (v->size + new_size));
        if (data = NULL) {
            new_size /= 2;
            continue;
        }
        break;
    }
    // int *data = (int *)malloc(sizeof(int) * (v->size * 2));
    // int *data  = (int *)realloc(v->data, sizeof(int) * (v->size * 2));
    //if (data == NULL) return 0;
    if (new_size == 0) return 0;
    // memcpy(data, v->data, sizeof(int) * v->length);
    v->data = data;
    v->size += new_size;
    // v->size *= 2;
    // free(v->data);
    // v->data = data;
    printf("Vector expand\n");
    return 1;
}

int insert(Vector *v, int x, int index) {
    if (v->length >= v->size) {
        if (!expand(v)) {
            return 0;
        }
    }
    if (index < 0 || index > v->length) {
        return 0;
    }
    // memmove
    for (int i = v->length - 1; i >= index; i--) {
        v->data[i + 1] = v->data[i];
    }
    v->data[index] = x;
    v->length += 1;
    return 1;
}

int delete_element(Vector *v, int ind) {
    if (ind >= v->length || ind < 0) {
        return 0;
    }
    for (int i = ind + 1; i < v->length; i++) {
        v->data[i - 1] = v->data[i];
    }
    v->length -= 1;
    return 1;
}

void output(Vector *v) {
    printf("[");
    for (int i = 0; i < v->length; i++) {
        printf(" %d", v->data[i]);
    }
    printf(" ]\n");
    return ;
}

void clear(Vector * v) {
    if (v == NULL) return ;
    free(v->data);
    free(v);
    return ;
}

int main() {
    srand(time(0));
    Vector *v = NULL;
    v = init();
    for (int i = 0; i < 10; i++) {
        int x = rand() % 100, ind = rand() % (i + 3) - 1;
        printf("%d : ", i + 1);
        printf("insert(%d, %d) = ", x, ind);
        int ret = insert(v, x, ind);
        printf("%d :", ret);
        output(v);
    }
    for (int i = 0; i < 5; i++) {
        int ind = rand() % (v->length + 2) - 1;
        printf("%d : delete_element(%d) = ", i + 1, ind);
        int ret = delete_element(v, ind);
        printf("%d :", ret);
        output(v);
    }
    return 0;
}
