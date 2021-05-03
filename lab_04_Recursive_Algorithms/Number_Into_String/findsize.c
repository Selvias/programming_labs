#include "func.h"

int findsize(int v) {

    int size = 1;

    while ((v = (v / 10)) != 0)
        size++;

    return size;
}