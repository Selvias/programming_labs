#pragma once
#include <stdio.h>
#include <stdlib.h>

enum {
    MAX_PATH = 260
};

int input(char**path);
int check(char *str, char *fbs);