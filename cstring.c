#include "cstring.h"

#include <stdio.h>
#include <ctype.h>

void scan(char* buf) {
    int i = 0;
    for (; !isspace(buf[i] = getchar()); ++i);
    buf[i] = '\0';
    return;
}
