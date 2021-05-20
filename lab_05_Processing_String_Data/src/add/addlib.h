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

int input(char**path);
int symcnt (char *arr, char sym);
void putstring(char *str, int count);


int check(char *str, char *fbs);
int process(char *str, char *fbs);
void divide(char *str, toks **token, int num);