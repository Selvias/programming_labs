#include "addlib.h"
#include "strings.h"

int process(char *str, char **subst, char *fbs) {

    char **subst_tok = (char **)malloc(MAX_PATH*sizeof(char *));
    char *path = (char *)malloc(MAX_PATH*sizeof(char));

    int count = stok(str, '+', subst);
    printf("Count of substrings : %d\n", count);

    putstring(str, count);

    int count_2 = 0;
    
    for (int i = 0; i < count; i++) {
        path = scpy(subst[i]);

        printf("%s", path);

        if (i == 0)
            printf("\n");

        //+2 для того, чтобы опустить первые два слэша. По крайней мере, пока не пойму, что с ними делать...

        count_2 = stok(path + 2, '\\', subst_tok);

        putstring(path + 2, count_2);
        printf("\n");
    }

    free(path);

    return 0;
}