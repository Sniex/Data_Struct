/*************************************************************************
	> File Name: 11.hash.cpp
	> Author: Yu_dong
	> Mail: 1124250973@qq.com
	> Created Time: 2018年07月28日 星期六 16时20分40秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 冲突处理 拉链法

typedef struct Data {
    char *str;
    struct Data *next;
} Data;

typedef struct HashTable {
    Data *data;
    int size;
    int cnt;
    int (*hash_func)(const char *);
} HashTable;


int APHash(const char *str) {
    int hash = 0;
    for (int i = 0; str[i]; i++) {
        if (i & 1) {
            hash ^= (hash << 7) ^ str[i] ^ (hash >> 3);
        } else {
            hash ^= (~((hash << 11) ^ str[i] ^ (hash >> 5)));
        }
    }
    return hash & 0x7ffffff;
}

int BKDRHash(const char *str) {
    int hash = 0, seed = 171;
    for (int i = 0; str[i]; i++) {
        hash = hash * seed + str[i];
    }
    return hash & 0x7ffffff;
}

int zobrist_table[50][256] = {0};

void init_zobrist_table() {
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 256; j++) {
            zobrist_table[i][j] = rand();
        }
    }
    return ;
}

int ZobristHash(const char *str) {
    static int flag = 1;
    if (flag) {
        flag = 0;
        init_zobrist_table();
    }
    int hash = 0;
    for (int i = 0; str[i]; i++) {
        hash ^= zobrist_table[i][str[i]];
    }
    return hash & 0x7fffffff;
}

int MyHash(const char *str) {
    int hash = 1;
    for (int i = 0; i < str[i]; i++) {
        hash *= str[i];
    }
    return hash & 0x7fffffff;
}


HashTable *init(int size, int (*func)(const char *)) {
    HashTable *p = (HashTable *)malloc(sizeof(HashTable));
    p->data = (Data *)calloc(sizeof(Data), size);
    p->size = size;
    p->cnt = 0;
    p->hash_func = func;
    return p;
}

void clear(HashTable *h) {
    if (h == NULL) return ;
    free(h->data);
    free(h);
    return ;
}

int query(HashTable *h, const char *str) {
    int ind = h->hash_func(str) % h->size;
    Data *p = h->data[ind].next;
    while (p) {
        if (strcmp(p->str, str) == 0) return -1;
        p = p->next;
        h->cnt += 1;
    }
    return ind;
}

void insert(HashTable *h, const char *str) {
    int ind = query(h, str);
    if (ind == -1) return ;
    Data *data = (Data *)malloc(sizeof(Data));
    data->str = strdup(str);
    data->next = h->data[ind].next;
    h->data[ind].next = data;
    return ;
}



int main() {
    #define HASH_TABLE_SIZE 100000
    srand(time(0));
    HashTable *apHashtable = init(HASH_TABLE_SIZE, APHash);
    HashTable *bkdrHashtable = init(HASH_TABLE_SIZE, BKDRHash);
    HashTable *zobristHashtable = init(HASH_TABLE_SIZE, ZobristHash);
    HashTable *MyHashtable = init(HASH_TABLE_SIZE, MyHash);
    #define MAX_TEST_CNT 100000
    for (int i = 0; i < MAX_TEST_CNT; i++) {
        char str[7] = {0};
        for (int j = 0; j < 6; j++) {
            str[j] = rand() % 26 + 'a';
        }
        str[6] = 0;
        insert(apHashtable, str);
        insert(bkdrHashtable, str);
        insert(zobristHashtable, str);
        insert(MyHashtable, str);
    }
    printf("APHash(%d) = %d\n", MAX_TEST_CNT, apHashtable->cnt);
    printf("BKDRHash(%d) = %d\n", MAX_TEST_CNT, bkdrHashtable->cnt);
    printf("zobristHash(%d) = %d\n", MAX_TEST_CNT, zobristHashtable->cnt);
    printf("MyHash(%d) = %d\n", MAX_TEST_CNT, MyHashtable->cnt);
    #undef MAX_TEST_CNT
    return 0;
}

