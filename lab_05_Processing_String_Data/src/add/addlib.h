#pragma once
#include <stdio.h>
#include <stdlib.h>

enum {
    MAX_PATH = 260,
    IP_LEN = 15,
    DOMAIN_LEN = 30,
    UNC_F = 2
};

typedef struct toktable_ip {

    char unc_root[UNC_F];
    char ip[IP_LEN];
    char directs[MAX_PATH - IP_LEN - UNC_F];

} paths_ip[1024];

typedef struct toktable_domain {

    char domain[DOMAIN_LEN];
    char directs[MAX_PATH - DOMAIN_LEN];

} paths_domain[1024];

int input(char**path);
int check(char *str, char *fbs);
int process(char *str, char **subst, char *fbs);
void putstring(char *str, int count);