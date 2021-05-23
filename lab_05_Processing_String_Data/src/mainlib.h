#pragma once
#include <stdio.h>
#include <stdlib.h>

enum {
    MAX_PATH = 260,
    NODE = 30,
};

typedef struct {

    char **ntoks;
    char node[NODE];
    char **dtoks;
    char directs[MAX_PATH - NODE];

} toks;

int input(char **path);
int check(char *str, char *fbs);
int process(char *str, char *fbs);
void putstring(char *str, int count);

int slen(char *str);
char *scpy(char *str);
int scmp(char *s1, char *s2);
int schr(char *str, char delim);
int stok(char *str, char delim, char **ptr);
int scspn(char *str, char *fbs);