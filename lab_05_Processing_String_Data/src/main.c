#include "mainlib.h"

int main() {

    char fbs[8] = {':', '*', '?', '"', '<', '>', '|', '\0'};
    //char fbs_name[9] = {'\\', '/', ':', '*', '?', '"', '<', '>', '|'};

    char *path = (char *)malloc(1024*sizeof(char));

    input(&path);
    int fc = check(path, fbs);

    if (fc < 0)
        printf("Too many characters.\n");
    else if (fc > 0)
        printf("The path contains forbidden characters.\n");

    putstring(path);
    // printf("\n");
    
    return 0;
}