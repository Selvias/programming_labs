#include "func.h"

int degree (int n, int deg)  {

    if (deg == 1)
        return n;

    return n * degree (n, deg - 1) ;
}