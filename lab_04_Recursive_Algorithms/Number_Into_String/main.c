#include "func.h"

int main() {

    int value = 1275;

    int len = findsize(value);
    char *string = NULL;
    string = (char*)malloc(len*sizeof(char));

    int deg = degree(10, len - 1);

    intostring(value, string, 0, deg);

    printf("%s\n", string);

    free(string);

    return 0;
}