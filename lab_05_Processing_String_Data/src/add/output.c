#include "addlib.h"

void putstring(char *str, int count) {
    int i = 0;

    for (int t = 0; t < count; t++) {
        while(str[i] != '\0') {
            printf("%c", str[i]);
            i++;
        }
        i++;
        printf("\n");
    }
}