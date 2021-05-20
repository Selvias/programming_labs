#include "addlib.h"
#include "strings.h"

int process(char *str, char *fbs) {



    // char **subst_tok = (char **)malloc(MAX_PATH*sizeof(char *));
    // char *path = (char *)malloc(MAX_PATH*sizeof(char));

    //Подсчёт, под какое количество указателей на подстроки необходимо выделить память
    int scount = symcnt (str, '+');
    char **subst = (char **)malloc(scount*sizeof(char *));
    toks **tokens = (toks **)malloc(sizeof(toks *));
    *tokens = (toks *)malloc(scount * sizeof(toks));



    stok(str, '+', subst);
    putstring(str, scount);
    printf("\n");
    // printf("Count of substrings : %d\n", scount);

    //Заполнение по структуре
    for (int i = 0; i < scount; i++) {
        divide(subst[i], tokens, i);
        printf("%s\n", ((*tokens)[i]).node);
        printf("%s\n", ((*tokens)[i]).directs);
    }

    //Разбиение "токенов" на меньшие единицы для проверки
    for (int i = 0; i < scount; i++) {
        int atom = symcnt (((*tokens)[i]).directs, '\\');
        ((*tokens)[i]).dtoks = (char **)malloc(atom*sizeof(char *));
        stok(((*tokens)[i]).directs, '\\', ((*tokens)[i]).dtoks);
        for (int j = 0; j < atom; j++)
            printf("%s\n", ((*tokens)[i]).dtoks[j]);

        printf("\n");

        int atom_2 = symcnt (((*tokens)[i]).node, '.');
        ((*tokens)[i]).ntoks = (char **)malloc(atom_2*sizeof(char *));
        stok(((*tokens)[i]).node, '.', ((*tokens)[i]).ntoks);
        for (int j = 0; j < atom_2; j++)
            printf("%s\n", ((*tokens)[i]).ntoks[j]);

        printf("\n");
    }

    // int count_2 = 0;
    
    // for (int i = 0; i < count; i++) {
    //     path = scpy(subst[i]);

    //     printf("%s", path);

    //     if (i == 0)
    //         printf("\n");

    //     //+2 для того, чтобы опустить первые два слэша. По крайней мере, пока не пойму, что с ними делать...

    //     count_2 = stok(path + 2, '\\', subst_tok);

    //     putstring(path + 2, count_2);
    //     printf("\n");
    // }

    // free(path);

    return 0;
}