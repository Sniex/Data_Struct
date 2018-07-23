/*************************************************************************
	> File Name: 4.stack.cpp
	> Author: Yu_dong
	> Mail: 1124250973@qq.com
	> Created Time: 2018年07月19日 星期四 11时46分01秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define data_type int
#define NULL_VALUE 0

typedef struct Stack {
    data_type *data;
    int top, size;
} Stack;

Stack *init(int n);
void clear(Stack *);
data_type top(Stack *);
int push(Stack *, data_type);
int pop(Stack *);
int empty(Stack *);
void output(Stack *); 

int main() {
    srand(time(0));
    Stack *s = init(100);
    for (int i = 0; i < 20; i++) {
        int op = rand() % 2, value = rand() % 100;
        switch (op) {
            case 0: {
                printf("push element = %d to stack\n", value);
                push(s, value);
                output(s);
            } break;
            case 1: {
                printf("pop element from stack = %d\n", i);
                pop(s);
                output(s);
            } break;
            default:
            fprintf(stderr, "error operator = %d\n", op);
            break;
        }
    }
    
    clear(s);
    
    
    return 0;
}

Stack *init(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (data_type *)malloc(sizeof(data_type) * n);
    s->size = n;
    s->top = -1;
    return s;
}

void clear(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}
data_type top(Stack *s) {
    if (empty(s)) return NULL_VALUE;
    return s->data[s->top];
}

int push(Stack *s, data_type value) {
    if (s->top + 1 == s->size) {
        return 0;
    }
    s->top += 1;
    s->data[s->top] = value;
    return 1;
}
int pop(Stack *s) {
    if (empty(s)) return 0;
    s->top -= 1;
    return 1;
}

int empty(Stack *s) {
    return s->top == -1;
}

void output(Stack *s) {
    //if (empty(s)) {
    //    printf("[]\n");
    //    return ;
    //}
    printf("[");
    int i;
    for (i = 0; i < s->top; i++) {
        printf("%d, ", s->data[i]);
    }
    printf("]\n");
    if (s->top > 0) {
        for (int j = 0; j < i - 1; j++) {
            printf("    ");
        }
        printf(" ↑\n");
        for (int j = 0; j < i - 1; j++) {
            printf("    ");
        }
        printf("top\n");
    }
}

