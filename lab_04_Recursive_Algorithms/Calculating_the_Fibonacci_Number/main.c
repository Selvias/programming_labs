#include "func.h"

int main () {

    int x = 1;
    int y = 1;

    int num = 10;

    int rez;

    rez = fibrec(num - 1);
    printf("REC_RESULT : %d\n", rez);

    rez = fibiter(num - 1, x, y);
    printf("ITER_RESULT : %d\n", rez);

    return 0;
}