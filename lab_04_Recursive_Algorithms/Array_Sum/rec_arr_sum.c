#include "mainlib.h"

int rec_arr_sum (int *arr, int n) {

    if (n == 0)
        return arr[0];

    return (arr[n] + rec_arr_sum (arr, n - 1));
}