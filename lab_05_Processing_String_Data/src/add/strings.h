#pragma once
#include <stdio.h>
#include <stdlib.h>

int slen(char *str);
char *scpy(char *str);

int scmp(char *s1, char *s2);
int schr(char *str, char delim);
int stok(char *str, char delim, char **ptr);
int scspn(char *str, char *fbs);