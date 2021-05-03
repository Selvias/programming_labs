#include "func.h"

char *intostring(int n, char *str, int c, int d) {

    if (d == 0)
        return str;

    int a = n / d;

    str[c] = a | 0x30;
    c++;
    n = n % d;
    d = d / 10;

    return (intostring(n, str, c, d));
}