#include "mainlib.h"

int main () {

    int *source = NULL;
    source = (int*)calloc(10, sizeof(int));
    if (source == NULL)
        return -1;

    for (int i = 0; i < 10; i++)
        source[i] = i;

    int sum = rec_arr_sum (source, 10 - 1);

    printf("RESULT : %d\n", sum);

    return 0;
}
