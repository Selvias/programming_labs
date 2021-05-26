#include "./add/addlib.h"

int main() {

    char fbs[10] = {'/', '\\',':', '*', '?', '"', '<', '>', '|', '\0'};

    char *path = (char *)malloc(1024*sizeof(char));
    if (path == NULL)
        return -1;

    char *delim = (char*)malloc(sizeof(char));
    if (delim == NULL)
        return -1;

    input(&path, &delim);

    process(path, *delim, fbs);

    free(path);
    free(delim);
    
    return 0;
}