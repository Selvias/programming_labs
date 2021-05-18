#include "mainlib.h"

int main() {

    char fbs[10] = {'/', '\\',':', '*', '?', '"', '<', '>', '|', '\0'};
    char **subst = (char **)malloc(1024*sizeof(char *));

    char *path = (char *)malloc(1024*sizeof(char));

    input(&path);

    process(path, subst, fbs);

    free(subst);
    free(path);
    
    return 0;
}