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
    int i = 2;
    while (str[i] != '\\') {
        ((*token)[num]).node[i - 2] = str[i];
        i++;
    }
    int t = ++i;
    while (str[i] != '\0') {
        ((*token)[num]).directs[i - t] = str[i];
        i++;
    }
}
//Синтаксический анализ
