#include "mainlib.h"

int main () {

    int *source = NULL;
    source = (int*)calloc(10, sizeof(int));
    if (source == NULL)
        return -1;

    for (int i = 0; i < 10; i++)
        source[i] = i;

    int sum = rec_arr_sum (source, 10 - 1);

    int sum_2 = 0;
    iter_arr_sum (source, 10 - 1, &sum_2);

    printf("RESULT : %d %d\n", sum, sum_2);

    free(source);

    return 0;
}
