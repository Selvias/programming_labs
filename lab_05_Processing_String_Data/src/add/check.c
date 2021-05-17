#include "addlib.h"
#include "strings.h"

int check(char *str, char *fbs) {
    int len = slen(str);
    if (len > MAX_PATH)
        return -1;
    
    int f = scspn(str, fbs);
    if (f <= len) {
        printf("flag : %d\n", f);
        printf("len : %d\n", len);
        return 1;
    }

    printf("flag : %d\n", f);
    printf("len : %d\n", len);

    return 0;
}