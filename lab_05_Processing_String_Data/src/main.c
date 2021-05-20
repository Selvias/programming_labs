#include "mainlib.h"

int main() {

    char fbs[10] = {'/', '\\',':', '*', '?', '"', '<', '>', '|', '\0'};

    char *path = (char *)malloc(1024*sizeof(char));
    input(&path);

    process(path, fbs);

    free(path);
    
    return 0;
}