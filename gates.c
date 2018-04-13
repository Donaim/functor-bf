#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "indexed_succ.h"

#define uint unsigned int
#define uchar unsigned char
#define MAX_OP_NUM 7

typedef struct {
    uchar a, b, c, d;
} func;
typedef struct {
    func arr[MAX_OP_NUM];
    uint size;
} farr;
typedef struct {
    Pair arr[MAX_OP_NUM];
    uint size;
} oparr;

#define nand(x, y) (! (x && y)) 

func tnand(const func x, const func y) {
    func re;
    re.a = nand(x.a, y.a);
    re.b = nand(x.b, y.b);
    re.c = nand(x.c, y.c);
    re.d = nand(x.d, y.d);
    return re;
}
#define func_equal(x, y) (x.a == y.a && x.b == y.b && x.c == y.c && x.d == y.d)

void print_func(func o) {
    printf("%d %d %d %d\n", o.a, o.b, o.c, o.d);
}

const func X = { 0, 1, 0, 1 };
const func Y = { 0, 0, 1, 1 };
const func T = { 1, 1, 1, 1 };
const func F = { 0, 0, 0, 0 };

#define CORELEN 2

uint powi(uint base, uint x) {
    uint re = 1;
    while (base-- > 0) { 
        re *= x;
    }
    return re;
}
uint get_count(uint num_steps, uint min_num) {
    uint re = 1;
    for (int i = min_num, to = min_num + num_steps; i < to; ++i) {
        re *= (powi(2, i));
    }

    printf("count(%d,%d) = %d\n", num_steps, min_num, re);

    return re;
}

Pair ** create_sc(uint poss, uint oplen) {
    Pair ** re = (Pair**)malloc(poss * sizeof(Pair*));
    for (uint i = 0; i < poss; ++i) {
        re[i] = (Pair*)malloc(oplen * sizeof(Pair));
    }
    return re;
}
void free_sc(Pair ** sc, uint poss) {
    for (uint i = 0; i < poss; i++) {
        free(sc[i]);
    }
    free(sc);
}

oparr bruteforce(const func desired) {
    printf("searching for: ");
    print_func(desired);

    func core[CORELEN];
    core[0] = X;
    core[1] = Y;

    for (int oplen = 0; oplen <= MAX_OP_NUM; oplen++) {
        uint poss_count = get_count(oplen, CORELEN);
        Pair ** sc = create_sc(poss_count, oplen);

        for (int o = 0; o < oplen; o++) {
            Pair pair = { 0, 0 };
            uint base = CORELEN + o;
            for (int k = 0; k < poss_count; k++) {
                // printf("pair = ");
                // print_pair(pair);
                // printf("\n");
                sc[k][o] = pair;
                increment_pair(&pair, base);
            }
        }

        farr be;
        be.size = CORELEN + oplen;
        for (int j = 0; j < CORELEN; j++) { be.arr[j] = core[j]; }

        for (int i = 0; i < poss_count; ++i) {
            for (int k = CORELEN; k < be.size; ++k) {
                Pair p = sc[i][k - CORELEN];
                be.arr[k] = tnand(be.arr[p.a], be.arr[p.b]);
            }

            if (func_equal(be.arr[be.size - 1], desired)) {
                printf("Found be = ");
                print_func(be.arr[be.size - 1]);
                oparr re;
                re.size = oplen;
                for (int k = 0; k < oplen; k++) {
                    re.arr[k] = sc[i][k];
                }
                return re;
            }
        }

        free_sc(sc, poss_count);
        printf("\n");
    }

    printf("Could not find ");
    print_func(desired);
    printf(" in %d operations\n", MAX_OP_NUM);
}

int main() {
    func desired = { 1, 0, 0, 0 };
    oparr found = bruteforce(desired);

    printf("Operations: ");
    for (int i = 0; i < found.size; i++) {
        print_pair(found.arr[i]);
        if (i != found.size - 1) { printf("->"); }
        else { printf("\n"); }
    }

    return 0;
}
