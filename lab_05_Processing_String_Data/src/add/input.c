#include "addlib.h"

int input(char **path, char **delim) {

    printf("Enter path : ");

    fgets(*path, 1024, stdin);

    printf("Enter delim : ");
    scanf("%c", *delim);
    getchar();
    printf("\n");

    return 0;
}