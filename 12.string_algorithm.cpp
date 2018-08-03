/*************************************************************************
	> File Name: 12.string_algorithm.cpp
	> Author: Yu_dong
	> Mail: 1124250973@qq.com
	> Created Time: 2018年08月02日 星期四 20时35分41秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int BF(const char *text, const char *pattern, int *p_cnt) {
    #define cnt (*p_cnt)
    int len1 = strlen(text);
    int len2 = strlen(pattern);
    for (int i = 0; i < len1 - len2 + 1; i++, cnt++) {
        int flag = 1;
        for (int j = 0; pattern[j]; j++, cnt++) {
            if (text[i + j] == pattern[j]) continue;
            flag = 0;
        }
        if (flag) return 1;
    }
    #undef cnt
    return 0;
}

int KMP (const char *text, const char *pattern, int *p_cnt) {
    #define cnt (*p_cnt)
    #define RETURN(a) { \
        free(next); \
        return a; \
    }
    int len1 = strlen(text);
    int len2 = strlen(pattern);
    int *next = (int *)malloc(sizeof(int) * len2);
    next[0] = -1;
    int j = -1;
    for (int i = 1; i < len2; i++, cnt++) {
        while (j != -1 && pattern[j + 1] != pattern[i]) j = next[j], cnt++;
        if (pattern[j + 1] == pattern[i]) {
            j += 1;
        }
        next[i] = j;
    }
    j = -1;
    for (int i = 0; text[i]; i++, cnt++) {
        while (j != -1 && pattern[j + 1] != text[i]) j = next[j], cnt++;
        if (pattern[j + 1] == text[i]) j += 1;
        if (pattern[j + 1] == 0) RETURN(1);
    }
    RETURN(0);
    #undef RETURN
    #undef cnt
}




int main() {
    char str1[] = "Hello World!";
    int cnt = 0;
    printf("BF(%s, %s) = %d\n", str1, "Wor", BF(str1, "Wor", &cnt));
    printf("BF search cnt = %d\n", cnt);
    cnt = 0;
    printf("KMP(%s, %s) = %d\n", str1, "Wor", KMP(str1, "Wor", &cnt));
    printf("KMP search cnt = %d\n", cnt);
    


    return 0;
}
