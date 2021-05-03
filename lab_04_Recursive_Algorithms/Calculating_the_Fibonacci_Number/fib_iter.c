#include "func.h"

int fibiter(int n, int a, int b) {

    if (n == 1)
        return b;

    int tmp = a;
    a = b;
    b = b + tmp;

    n--;

    return fibiter(n, a, b);

}