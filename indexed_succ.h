#pragma once

#include <stdio.h>

#define uint unsigned int
#define uchar unsigned char

typedef struct {
    uchar a, b;
} Pair; 

void print_pair(Pair p) {
    printf("(%d,%d)", p.a, p.b);
}

int increment_arr(uchar * arr, uint size, uint base) {
     for (int i = 0; i < size; i++) {
        if (arr[i] + 1 < base) {
            ++arr[i];
            return 1;
        }
        arr[i] = 0;
    }
    return 0;
}
int increment_mult_bases(uchar * arr, uint size, uchar * bases) { // return 0 on overflow
    for (int i = 0; i < size; i++) {
        if (arr[i] + 1 < bases[i]) {
            ++arr[i];
            return 1;
        }
        arr[i] = 0;
    }
    return 0;
}

int increment_pair(Pair * p, uint base) {
    if (p->a + 1 < base) {
        ++(p->a);
    } else 
    if (p->b + 1 < base) {
        ++(p->b);
        p->a = 0;
    } else { // overflow
        p->a = 0;
        p->b = 0;
        return 0;
    }
    return 1;
}
