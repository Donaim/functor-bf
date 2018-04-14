#include <stdio.h>
#include "indexed_succ.h"

#define uint unsigned int
#define uchar unsigned char

#define CORELEN 2
#define MAX_OP_NUM 7

typedef struct {
    uchar a, b, c, d;
} func;
typedef struct {
    Pair arr[MAX_OP_NUM];
    uint size;
} oparr;

#define nand(p, q) (!(p && q)) 

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
    printf("%d %d %d %d\n", o.a, o.b, o.c, o.d);
}

const func X = { 0, 0, 1, 1 };
const func Y = { 0, 1, 0, 1 };
const func T = { 1, 1, 1, 1 };
const func F = { 0, 0, 0, 0 };

oparr bruteforce(const func desired) {
    printf("\nsearching for: ");
    print_functor(desired);

    func core[4] = { X, Y, T, F };

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
                tnandf(be[p.a], be[p.b], be[CORELEN + k]);
            }
            if (func_equal(be[CORELEN + oplen - 1], desired)) {
                oparr re;
                re.size = oplen;
                for (int k = 0, j = 0; k < oplen; ++k, j += 2) {
                    Pair p = { counter[j], counter[j + 1] };
                    re.arr[k] = p;
                }
                return re;
            }
        } while(increment_mult_bases(counter, oplen * 2, bases));
    }

    printf("\nCould not find ");
    print_functor(desired);
    printf(" in %d operations\n", MAX_OP_NUM);
}

void find_hardest() {
    uchar inc[4] = { 0, 0, 0, 0 };
    
    func hardest_functor;
    uint hardest_oplen = 0;
    
    do {
        func desired = { inc[3], inc[2], inc[1], inc[0] };

        oparr found = bruteforce(desired);
        // printf("found in %d operations\n", found.size);

        if (found.size > hardest_oplen) {
            hardest_oplen = found.size;
            hardest_functor = desired;
        }
    } while (increment_arr(inc, 4, 2));

    printf("\nchecked all. hardest was: ");
    print_functor(hardest_functor);
    printf(" needed %d operations to get\n", hardest_oplen);
}
void find_xor() {
    func desired = { 0, 1, 1, 0 };
    oparr found = bruteforce(desired);

    printf("Operations: ");
    for (int i = 0; i < found.size; i++) {
        print_pair(found.arr[i]);
        if (i != found.size - 1) { printf("->"); }
    }
    printf("\n");
}

int main() {
    // find_xor();
    find_hardest();

    return 0;
}
