#include "addlib.h"
#include "strings.h"

//Подсчёт количества символов в строке
int symcnt (char *arr, char sym) {

    int i = 0, counter = 0;

    while (arr[i] != '\0') {
        if (arr[i] == sym)
            counter++;
        i++;
    }

    return counter + 1;
}
//Вывод строк
void putstring(char *str, int count) {
    int i = 0;

    for (int t = 0; t < count; t++) {
        while(str[i] != '\0') {
            printf("%c", str[i]);
            i++;
        }
        i++;
        if (t == count - 1)
            break;
        printf("\n");
    }
}
//Заполнение структуры токенов
void divide(char *str, toks **token, int num) {

    if ((*token)[num].sizeflag == -1) {
        return;
    }

    int i = 0;

    ((*token)[num]).protocol[2] = '\0';

    while(i < 2) {
        if (str[i] == '\\')
            ((*token)[num]).protocol[i] = str[i];
        else {
            printf("Uncorrect protocol : %s\n", str);
            i = 2;
            break;
        }
        i++;
    }
    while (str[i] != '\\') {
        ((*token)[num]).node[i - 2] = str[i];
        i++;
    }
    int t = i;
    while (str[i] != '\0') {
        ((*token)[num]).directs[i - t] = str[i];
        i++;
    }
}
//Синтаксический анализ

//Проверка на домен
int onlyletters(toks *token) {

    if ((*token).sizeflag == -1) {
        return -1;
    }

    for (int i = 0; i < token->nnodes; i++) {
        for (int j = 0; token->ntoks[i][j] != '\0'; j++) {
            if ((*token).ntoks[i][j] > 'z' || token->ntoks[i][j] < 'a')
                return -1;
        }
    }
    //Если вернёт ноль, то запустить проверку на принадлежность верхнего домена на принадлежность com, ru, org
    return 0;
}

//Проверка на IP
int onlynumbers(toks *token) {

    if ((*token).sizeflag == -1) {
        return -1;
    }

    for (int i = 0; i < token->nnodes; i++) {
        for (int j = 0; token->ntoks[i][j] != '\0'; j++) {
            if ((*token).ntoks[i][j] > '9' || token->ntoks[i][j] < '0')
                return -1;
        }
    }
    //Если вернёт ноль, то запустить проверку токенов IP адреса на принадлежность диапазону 0 <= x <= 255
    return 0;
}

int string_into_number(char *str) {
    int len = slen(str);
    int paw = degree(10, len);

    int num = 0;

    for (int i = 0; i <= len; i++) {
        num = num + (str[i] - TONUM) * paw;
        paw /= 10;
    }

    return num;
}

int checknode(toks *token) {

    if (scmp(token->ntoks[token->nnodes - 1], "com") == 0 || scmp(token->ntoks[token->nnodes - 1], "ru") == 0  || scmp(token->ntoks[token->nnodes - 1], "org") == 0 ) {
        return 0;
    }
    return -1;
}

int checkip(toks *token) {
    for (int i = 0; i < token->nnodes; i++) {
        int num = string_into_number((*token).ntoks[i]);
        if (num > 255 || num < 0) {
            return -1;
        }
    }
    return 0;
}

int degree (int n, int deg) {

    if (deg == 1)
        return n;
    if (deg == 0)
        return 1;

    return n*degree(n, deg - 1);
}
