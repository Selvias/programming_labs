#include <stdio.h>
#include <string.h>
#include "command.h"

int main(int argc, char *argv[])
{
    // argc - количество аргументов
    // argv - массив указателей на строки.
    // Нулевой элемент - командна запуска приложения

    int i;
    for (i = 0; i < argc; ++i) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    //Проверка запуска программы из командной строки на корректность

    if (i != 4 || (strcmp(argv[1], "code") != 0 && strcmp(argv[1], "decode") != 0) || (strcmp(argv[2], "points.txt") && strcmp(argv[2], "units.bin")) || (strcmp(argv[3], "points.txt") && strcmp(argv[3], "units.bin"))) {
        printf("Usage:\ncoder encode <in-file-name> <out-file-name>\ncoder decode <in-file-name> <out-file-name>\n");
        return -1;
    }

    //Назначение аргументов командной строки

    char *command = argv[1];
    const char *in_file_name = argv[2];
    const char *out_file_name = argv[3];

    //Выбор режима (кодирование / декодирование)

    if (strcmp(command, "code") == 0)
        encode_file(in_file_name, out_file_name);
    else if (strcmp(argv[1], "decode") == 0)
        decode_file(in_file_name, out_file_name);

    return 0;
}