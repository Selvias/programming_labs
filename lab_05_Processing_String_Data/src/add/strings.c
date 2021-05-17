#include "strings.h"
//Длина строки
int slen(char *str) {

    int len;

    for (int i = 0; str[i] != '\0'; i++)
        len = i;

    return len;
}
//Копирование строки
char *scpy(char *str) {

    int i;
    int len = slen(str);

    char *scopy = (char *)malloc((len + 1)*sizeof(char));

    for(i = 0; str[i] != '\0'; i++)
        scopy[i] = str[i];

    scopy[i] = '\0';

    return scopy;
}
//Сравнение строк по алфавиту
int scmp(char *s1, char *s2) {
    int i, flag = 0;

    for(i = 0; (s1[i] == s2[i]) && s1[i] != '\0' && s2[i] != '\0'; i++);

    if (s1[i] < s2[i])
        flag = -1;
    else if (s1[i] > s2[i])
        flag = 1;

    return flag;
}
//Поиск символа в строке
int schr(char *str, char delim) {
    int i, indx = -1;

    for (i = 0; (str[i]) != '\0' && (str[i] != delim); i++);

    if (str[i] == delim)
        indx = i;

    return indx;
}
//Разбиение строки на поля
int stok(char *str, char delim, char **ptr) {
    char *suf = str;
    //ptr - массив указателей на подстроки
    ptr[0] = str;

    int i, j = 1;

    while((i = schr(suf, delim)) >= 0) {
        suf[i] = '\0';
        //Перемещение указателя к след. части строки. Для функции поиска символа в строке suf - каждый раз новая строка
        suf = suf + i + 1;
        //Присваивание указателя на отдельное поле
        ptr[j] = suf;
        j++;
    }
    
    //Количество подстрок в строке str
    return j;
}
//Проверка строки на недопустимые символы
int scspn(char *str, char *fbs) {
    int i;
    
    for (i = 0; str[i] != '\0'; i++) {
        if (schr(fbs, str[i]) >= 0) {
            break;
        }
    }
    return i;
}