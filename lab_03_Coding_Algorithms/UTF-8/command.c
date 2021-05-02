#include "coder.h"
#include "command.h"
#include <stdlib.h>

int encode_file (const char *in_file_name, const char*out_file_name) {
    FILE *in;
    FILE *out;
    in = fopen(in_file_name, "r");
    out = fopen(out_file_name, "wb");

    CodeUnit enc_point;
    uint32_t point;

    while (!feof(in)) {
        fscanf(in, "%x", &point);
        encode(point, &enc_point);
        const CodeUnit *cd = (const CodeUnit *)&enc_point;
        write_code_unit(out, cd);
    }

    fclose(in);
    fclose(out);
    return 0;
}

int decode_file (const char *in_file_name, const char*out_file_name) {
    FILE *in;
    FILE *out;
    in = fopen(in_file_name, "rb");
    out = fopen(out_file_name, "w");

    CodeUnit *enc_point = (CodeUnit*)malloc(sizeof(CodeUnit));

    while (1) {
        read_next_code_unit(in, enc_point);
        const CodeUnit *c_unit = (const CodeUnit *) enc_point;
        uint32_t result = decode(c_unit);
        if (feof(in))
            break;
        fprintf(out, "%x\n", result);
    }

    fclose(in);
    fclose(out);
    return 0;
}