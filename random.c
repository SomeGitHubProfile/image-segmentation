#include "random.h"

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define MAX_UINT_VALUE_AS_DOUBLE 4294967295.0

bool inited = false;

void init_random(time_t time) {
    if (inited) {
        return;
    }
    srand(time);
    inited = true;
    return;
}


int randint() {
    return rand();
}

int randint_between(int left, int right) {
    if (right < left) {
        left ^= right;
        right ^= left;
        left ^= right;
    }
    return left + rand() % (right - left);
}

unsigned unsigned_randint() {
    return rand();
}

unsigned unsigned_randint_between(unsigned left, unsigned right) {
    if (right < left) {
        left ^= right;
        right ^= left;
        left ^= right;
    }
    return left + rand() % (right - left);
}

double random_01() {
    return unsigned_randint() / MAX_UINT_VALUE_AS_DOUBLE;
}