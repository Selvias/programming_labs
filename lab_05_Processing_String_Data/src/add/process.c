#include "addlib.h"
#include "strings.h"

int process(char *str, char delim, char *fbs) {

    //Подсчёт, под какое количество указателей на подстроки необходимо выделить память
    int scount = symcnt (str, delim);
    char **subst = (char **)malloc(scount*sizeof(char *));

    if (subst == NULL) {
        printf("Memory allocation failure\n");
        return -1;
    }

    toks **tokens = (toks **)malloc(sizeof(toks *));
    if (tokens == NULL) {
        printf("Memory allocation failure\n");
        free(subst);
        return -1;
    }
    *tokens = (toks *)malloc(scount * sizeof(toks));
    if (*tokens == NULL) {
        printf("Memory allocation failure\n");
        free(subst);
        free(tokens);
        return -1;
    }

    stok(str, '+', subst);

    for (int y = 0; y < scount; y++) {
        int size = slen(subst[y]);
        if (size > PATHMAXLEN) {
            (*tokens)[y].sizeflag = -1;
        }
        else if(subst[y][0] != '\\' || subst[y][1] != '\\') {
            (*tokens)[y].standardflag = -1;
        }
    }

    for (int y = 0; y < scount; y++) {
        if ((*tokens)[y].sizeflag == -1) {
            printf("\nIncorrect size\n");
        }
        else if ((*tokens)[y].standardflag == -1) {
            printf("Wrong standard\n");
        }
    }

    if (schr(str, '\\') == -1)
        return -1;

    //Заполнение по структуре
    for (int i = 0; i < scount; i++) {
        divide(subst[i], tokens, i);
    }

    int atom, atom_2;

    //Разбиение "токенов" на меньшие единицы для проверки
    for (int i = 0; i < scount; i++) {
        ((*tokens)[i]).dirs = atom = symcnt (((*tokens)[i]).directs, '\\');
        ((*tokens)[i]).dtoks = (char **)malloc(atom*sizeof(char *));
        if (((*tokens)[i]).dtoks == NULL) {
            printf("Memory allocation failure\n");
            for (int mem = 0; mem < i; mem++) {
                if ((*tokens)[mem].ntoks != NULL)
                    free((*tokens)[mem].ntoks);
                if((*tokens)[mem].dtoks != NULL)
                    free((*tokens)[mem].dtoks);
            }
            free(subst);
            free(*tokens);
            free(tokens);
            return -1;
        }
        stok(((*tokens)[i]).directs, '\\', ((*tokens)[i]).dtoks);

        ((*tokens)[i]).nnodes = atom_2 = symcnt (((*tokens)[i]).node, '.');
        ((*tokens)[i]).ntoks = (char **)malloc(atom_2*sizeof(char *));
        if (((*tokens)[i]).ntoks == NULL) {
            printf("Memory allocation failure\n");
            for (int mem = 0; mem < i; mem++) {
                if ((*tokens)[mem].ntoks != NULL)
                    free((*tokens)[mem].ntoks);
                if((*tokens)[mem].dtoks != NULL)
                    free((*tokens)[mem].dtoks);
            }
            free(subst);
            free(*tokens);
            free(tokens);
            return -1;
        }
        stok(((*tokens)[i]).node, '.', ((*tokens)[i]).ntoks);
    }

    putstring(str, scount);
    printf("\n");

    //Проверка на отсутствие запрещённых символов
    for (int k = 0; k < scount; k++) {
        for (int d = 1; d < (*tokens)[k].dirs; d++) {
            int check = scspn(((*tokens)[k]).dtoks[d], fbs);
            int len = slen(((*tokens)[k]).dtoks[d]);
            if (len >= check) {
                printf("Contains forbidden characters : \n");
                printf("%s\n", ((*tokens)[k]).dtoks[d]);
            }
        }
        for (int c = 1; c < (*tokens)[k].nnodes; c++) {
            int check = scspn(((*tokens)[k]).ntoks[c], fbs);
            int len = slen(((*tokens)[k]).ntoks[c]);
            if (len >= check) {
                printf("Contains forbidden characters : \n");
                printf("%s\n", ((*tokens)[k]).ntoks[c]);
            }
        }
    }

    //Проверка доменного имени на формат

    int form = -1, form_2 = -1, domain = -1, ip = -1;

    for (int b = 0; b < scount; b++) {
            form = onlyletters(&(*tokens)[b]);
            //Проверка на ip, если доменом не является
            if (form == -1) {
                form_2 = onlynumbers(&(*tokens)[b]);
                if (form_2 == -1) {
                    printf("Uncorrect IP : ");
                    for (int x = 0; x < (*tokens)[b].nnodes; x++) {
                        printf("%s", (*tokens)[b].ntoks[x]);
                        if (x < (*tokens)[b].nnodes -1)
                            printf(".");
                    }
                    printf("\n");
                    (*tokens)[b].flag = -1;
                }
                else if (form_2 == 0) {
                    ip = checkip(&(*tokens)[b]);
                    if (ip == 0) {
                        printf("Correct IP : ");
                        for (int x = 0; x < (*tokens)[b].nnodes; x++) {
                            printf("%s", (*tokens)[b].ntoks[x]);
                            if (x < (*tokens)[b].nnodes -1)
                                printf(".");
                        }   
                        printf("\n");
                        (*tokens)[b].flag = 0;
                    }
                    else if (ip == -1) {
                        printf("Uncorrect IP : ");
                        for (int x = 0; x < (*tokens)[b].nnodes; x++) {
                            printf("%s", (*tokens)[b].ntoks[x]);
                        if (x < (*tokens)[b].nnodes -1)
                            printf(".");
                        }
                        printf("\n");
                        (*tokens)[b].flag = -1;
                    }
                }
            }
            //Проверка на корректность доменного имени
            else if (form == 0) {
                domain = checknode(&(*tokens)[b]);
                if (domain == 0) {
                    printf("Correct domain : ");
                    for (int x = 0; x < (*tokens)[b].nnodes; x++) {
                        printf("%s", (*tokens)[b].ntoks[x]);
                        if (x < (*tokens)[b].nnodes -1)
                            printf(".");
                    }   
                    printf("\n");
                    (*tokens)[b].flag = 0;
                }
                else if (domain == -1) {
                    printf("Uncorrect domain : ");
                    for (int x = 0; x < (*tokens)[b].nnodes; x++) {
                        printf("%s", (*tokens)[b].ntoks[x]);
                        if (x < (*tokens)[b].nnodes -1)
                            printf(".");
                    }
                    printf("\n");
                    (*tokens)[b].flag = -1;
                }
            }
    }

    //Склейка (Сборка) и вывод форматных строк
    printf("\nResult : ");

    int nrez = 0;

    for (int s = 0; s < scount; s++) {
        if ((*tokens)[s].flag == 0 && scmp((*tokens)[s].protocol, "\\\\") == 0) {
            if (nrez != 0)
                printf("+");
            printf("http://");
            for (int g = 0; g < (*tokens)[s].nnodes; g++) {
                printf("%s", (*tokens)[s].ntoks[g]);
                if (g < (*tokens)[s].nnodes - 1)
                    printf(".");
            }
            for (int g = 0; g < (*tokens)[s].dirs; g++) {
                printf("%s", (*tokens)[s].dtoks[g]);
                if (g < (*tokens)[s].dirs - 1)
                    printf("/");
            }
            nrez++;
        }
        if (s == scount - 1) {
                printf("\n");
            }
    }

    for (int m = 0; m < scount; m++) {
        if ((*tokens)[m].ntoks != NULL)
            free((*tokens)[m].ntoks);
        if((*tokens)[m].dtoks != NULL)
            free((*tokens)[m].dtoks);
    }
    free(*tokens);
    free(tokens);
    free(subst);

    return 0;
}