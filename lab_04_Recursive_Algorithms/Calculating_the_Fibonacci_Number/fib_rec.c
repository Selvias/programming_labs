#include "func.h"

int fibrec(int n) {

    if (n == 0 || n == 1)
        return 1;

    return (fibrec(n - 1) + fibrec(n - 2));
}