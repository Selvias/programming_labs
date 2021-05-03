#include "mainlib.h"

int iter_arr_sum (int *arr, int len, int *rez) {

    if (len == 0) {
        *rez += arr[0];
        return 0;
    }

    *rez += arr[len];
    len--;
    return iter_arr_sum(arr, len, rez);

}