#include "command.h"
#include "coder.h"

int encode_file(const char *in_file_name, const char *out_file_name) {

    uint32_t point;
    CodeUnits *code = (CodeUnits *)malloc(sizeof(CodeUnits));

    FILE *input, *output;
    input = fopen(in_file_name, "r");
    output = fopen(out_file_name, "wb");

    printf("ENCODE MODE\n");

    while (!feof(input)) 
    {
        if (feof(input))
            break;
        fscanf(input, "%d", &point);
        encode(point, code);
        printf("CURRENT POINT : %d ", point);
        printf("LENGTH : %ld\n", code->length);
        fwrite(code->code, 1, code->length, output);
    }

    fclose(input);
    fclose(output);

    return 0;

}
int decode_file(const char *in_file_name, const char *out_file_name) {

    FILE *input, *output;
    input = fopen(in_file_name, "rb");
    output = fopen(out_file_name, "w");

    CodeUnits code_units;
    CodeUnit code_unit;
    code_unit.code = (uint8_t**)malloc(sizeof(uint8_t*));
    *code_unit.code = (uint8_t*)malloc(4*sizeof(uint8_t));
    // const CodeUnit code_unit_const;
    // const CodeUnit *cunt = &code_units;
    printf("DECODE MODE\n");

    while (!feof(input)) {
        read_next_code_unit(input, &code_units);
        for(int p = 0; p < 4; p++) {
            (*code_unit.code)[p] = code_units.code[p];
        }
        code_unit.length = code_units.length;
        const CodeUnit *cunt = &code_unit;
        decode(cunt);
        write_code_unit(output, cunt);
    }

    fclose(input);
    fclose(output);

    return 0;

}