#include "addlib.h"

int input(char **path) {

    printf("Enter path : ");

    fgets(*path, 1024, stdin);
    return 0;
}