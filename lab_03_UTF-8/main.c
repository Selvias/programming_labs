#include "coder.h"
#include "command.h"

int main (int argc, char **argv) {
    const char * cmd = argv[1];
    const char * from = argv[2];
    const char *to = argv[3];

    if (cmd == NULL) {
        printf ("Usage:\ncoder encode <in-file-name> <out-file-name>\ncoder decode <in-file-name> <out-file-name>\n");
        return -1;
    } 
    if (strcmp(cmd, "code") != 0 && strcmp(cmd, "decode") != 0) {
        printf ("Usage:\ncoder encode <in-file-name> <out-file-name>\ncoder decode <in-file-name> <out-file-name>\n");
        return -1;
    }
    if (from == NULL) {
        printf ("Usage:\ncoder encode <in-file-name> <out-file-name>\ncoder decode <in-file-name> <out-file-name>\n");
        return -1;
    }
    if (to == NULL) {
        printf ("Usage:\ncoder encode <in-file-name> <out-file-name>\ncoder decode <in-file-name> <out-file-name>\n");
        return -1;
    }

    if (strcmp(cmd, "code") == 0)
        encode_file (from, to);
    else if (strcmp(cmd, "decode") == 0)
        decode_file(from, to);

    return 0;
}