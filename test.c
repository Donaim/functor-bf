#include "gates.c"

uchar check_uniwersal(func f) {
    oparr re;
    uchar inc[4] = { 0, 0, 0, 0 };
    do {
        func desired = { inc[3], inc[2], inc[1], inc[0] };
        if( ! bruteforce(desired, f, &re) ) {
            return 0;
        }
    } while (increment_arr(inc, 4, 2));
    return 1;
}

void find_universal() {
    uchar inc[4] = { 0, 0, 0, 0 };
    uchar finc[4] = { 0, 0, 0, 0 };

    do {
        func f = { finc[3], finc[2], finc[1], finc[0] };
        printf("Checking ");
        print_functor(f);
        printf(" ... ");

        if (check_uniwersal(f)) { 
            printf("Yes\n");
        } else {
            printf("No\n");
        }

    } while(increment_arr(finc, 4, 2));
}
void find_hardest(func f) {
    uchar inc[4] = { 0, 0, 0, 0 };
    
    func hardest_functor;
    uint hardest_oplen = 0;
    oparr found;

    do {
        func desired = { inc[3], inc[2], inc[1], inc[0] };

        if( bruteforce(desired, f, &found) ) {
            if (found.size > hardest_oplen) {
                hardest_oplen = found.size;
                hardest_functor = desired;
            }
        } else {
            printf("Could not found ");
            print_functor(desired);
            printf(" in %d operations", MAX_OP_NUM);
        }

    } while (increment_arr(inc, 4, 2));

    printf("\nchecked all. hardest was: ");
    print_functor(hardest_functor);
    printf(" needed %d operations to get\n", hardest_oplen);
}
void find_xor() {
    func desired = { 0, 1, 1, 0 };
    func f = { 1, 1, 1, 0 };

    oparr found;
    if(bruteforce(desired, f, &found)) {
        printf("Operations: ");
        for (int i = 0; i < found.size; i++) {
            print_pair(found.arr[i]);
            if (i != found.size - 1) { printf("->"); }
        }
        printf("\n");
    } else {
        printf("Could not found ");
        print_functor(desired);
        printf(" in %d operations", MAX_OP_NUM);
    }
}

int main() {
    // find_xor();
    // find_hardest();
    find_universal();

    return 0;
}
