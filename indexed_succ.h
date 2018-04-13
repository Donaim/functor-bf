#pragma once

#include <stdio.h>

#define ARRSIZE 2
#define uint unsigned int
#define uchar unsigned char

typedef struct {
    uchar ptr[ARRSIZE];
    uchar size;
} Array;
typedef struct {
    uchar a, b;
} Pair;

void print_pair(Pair p) {
    printf("(%d,%d)", p.a, p.b);
}

void print_arr_rev(Array a) {
    printf("%c ", '{');
    for (int i = a.size - 1; i >= 0; --i) {
        printf("%d ", a.ptr[i]);
    }
    printf("%c\n", '}');
}

int find_last_index(uchar * arr, uint size, uint base)
{
    for (int i = 0; i < size; ++i) {
        if (arr[i] < base) { return i; }
    }
    return -1;
}
void increment_arr(Array * A, uint base) {
    --base;
    uchar * arr = A->ptr;
    if (arr[0] < base) {
        ++arr[0];
    } else {
        int last_index = find_last_index(arr, A->size, base);
        if (last_index > 0) {
            ++arr[last_index];
        } else {
            last_index = A->size;
            arr[last_index] = 1;
            A->size++;
        }

        for (int i = 0; i < last_index; ++i) {
            arr[i] = 0;
        }
    }
}
void increment_pair(Pair * p, uint base) {
    if (p->a < base - 1) {
        ++(p->a);
    } else 
    if (p -> b < base - 1) {
        ++(p->b);
        p->a = 0;
    } else { // overflow
        p->a = 0;
        p->b = 0;
    }
}
