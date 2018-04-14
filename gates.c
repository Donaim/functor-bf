#include <stdio.h>
#include "indexed_succ.h"

#define uint unsigned int
#define uchar unsigned char

#define CORELEN 2
#define MAX_OP_NUM 6

typedef struct {
    uchar a, b, c, d;
} func;
typedef struct {
    Pair arr[MAX_OP_NUM];
    uint size;
} oparr;

#define nand(p, q) (!(p && q)) 

uchar any(uchar p, uchar q, func z) {
    switch(p * 2 + q) {
        case 0: return z.a;
        case 1: return z.b;
        case 2: return z.c;
        default: return z.d;
    }
}
func tany(func x, func y, func z) {
    func re;
    re.a = any(x.a, y.a, z);
    re.b = any(x.b, y.b, z);
    re.c = any(x.c, y.c, z);
    re.d = any(x.d, y.d, z);
    return re;
}

func tnand(const func x, const func y) {
    func re;
    re.a = nand(x.a, y.a);
    re.b = nand(x.b, y.b);
    re.c = nand(x.c, y.c);
    re.d = nand(x.d, y.d);
    return re;
}
#define tnandf(x, y, re) \
    re.a = nand(x.a, y.a); \
    re.b = nand(x.b, y.b); \
    re.c = nand(x.c, y.c); \
    re.d = nand(x.d, y.d); \

#define func_equal(x, y) (x.a == y.a && x.b == y.b && x.c == y.c && x.d == y.d)

void print_functor(func o) {
    printf("[ %d %d %d %d ]", o.a, o.b, o.c, o.d);
}

const func X = { 0, 0, 1, 1 };
const func Y = { 0, 1, 0, 1 };
const func T = { 1, 1, 1, 1 };
const func F = { 0, 0, 0, 0 };

uchar bruteforce(const func desired, const func f, oparr * re) {
    const func core[4] = { X, Y, T, F };

    uchar bases[MAX_OP_NUM * 2];
    uchar counter[MAX_OP_NUM * 2];
    for (int i = 0; i < MAX_OP_NUM * 2; i++) 
    { 
        counter[i] = 0;
        bases[i]   = ((CORELEN + (i + 2)) / 2); 
    }

    func be[CORELEN + MAX_OP_NUM];
    for (int j = 0; j < CORELEN; j++) { be[j] = core[j]; }
    
    for (int oplen = 0; oplen <= MAX_OP_NUM; oplen++) {
        do {
            for (int k = 0, j = 0; k < oplen; ++k, j += 2) {
                Pair p = { counter[j], counter[j + 1] };
                // tnandf(be[p.a], be[p.b], be[CORELEN + k]);
                be[CORELEN + k] = tany(be[p.a], be[p.b], f);
            }
            if (func_equal(be[CORELEN + oplen - 1], desired)) {
                re->size = oplen;
                for (int k = 0, j = 0; k < oplen; ++k, j += 2) {
                    Pair p = { counter[j], counter[j + 1] };
                    re->arr[k] = p;
                }
                return 1;
            }
        } while(increment_mult_bases(counter, oplen * 2, bases));
    }

    return 0;
}
