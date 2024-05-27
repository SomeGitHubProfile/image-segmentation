#pragma once

#include <time.h>

#ifndef RANDOM
#define RANDOM
void init_random(time_t time);
int randint();
int randint_between(int left, int right);
unsigned unsigned_randint();
unsigned unsigned_randint_between(unsigned left, unsigned right);
double random_01();
#endif
