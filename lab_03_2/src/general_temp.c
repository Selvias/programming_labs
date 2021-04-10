#include "coder.h"
#include "command.h"
#include <stdio.h>

int encode(uint32_t code_point, CodeUnits *code_units);
uint32_t decode(const CodeUnit *code_unit);

int main(int argc, char *argv[])
{
    // argc - количество аргументов
    // argv - массив указателей на строки.
    // Нулевой элемент - командна запуска приложения

    int i;
    for (i = 0; i < argc; ++i) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    //Назначение аргументов командной строки

    char *command = argv[1];
    const char *in_file_name = argv[2];
    const char *out_file_name = argv[3];

    const CodeUnit *decode_buf;

        int count = 100;

    unsigned short int *size_x;
    size_x = (unsigned short int *)calloc(count, sizeof(unsigned short int));

    uint8_t* buffer = NULL;                                             //Выделить память
    buffer = (uint8_t*)malloc(4*sizeof(uint8_t)); 
    FILE *out_uncompressed;    
    FILE *out_compressed;
    FILE *out_decompressed;

    out_uncompressed = fopen("uncompressed.dat", "w");
    out_compressed = fopen("compressed.dat", "w");

    uint32_t digit = 0;

    for (int i = 0; i < 100; i++) {

        fprintf(out_uncompressed, "%d\n", digit = generate_number());   //Вызов генерации числа    

        int sz = encode_varint(digit, buffer);  
        size_x[i] = sz;

        fwrite(buffer, 1, sz, out_compressed);
    }

    fclose(out_uncompressed);
    fclose(out_compressed);

    out_compressed = fopen("compressed.dat", "r");
    out_decompressed = fopen("decompressed.dat", "w");

    uint8_t **val = (uint8_t**)malloc(sizeof(uint8_t*));

    const uint8_t **val_cp = (const uint8_t**)val;

    for (int i = 0; i < 100; i++) {

        *val = (uint8_t*)malloc(size_x[i]*sizeof(uint8_t));

        fread(*val, 1, size_x[i], out_compressed);

        uint32_t uncode = decode_varint(val_cp);
        fprintf(out_decompressed, "%u\n", uncode);

    }

    fclose(out_compressed);
    fclose(out_decompressed);

    free(val);
    // free(*val);
    free(size_x);
    free(buffer);

    return 0;
}

int encode(uint32_t code_point, CodeUnits *code_units) 
{
    assert((code_units != NULL) || (code_units->code != NULL));
    uint8_t* cur = code_units->code; 
                                  
    while (code_point >= 0x80) {                      
        const uint8_t byte = (code_point & 0x7f) | 0x80;                         
        *cur = byte;                                              
        code_point >>= 7;                                             
        ++cur;                                                   
    }             
    *cur = code_point;                                
    ++cur;           

    code_units->length = cur - code_units;  

    if (code_units != NULL && code_units->length != 0)
        return 0;
    else 
        return -1;
}

uint32_t decode(const CodeUnit *code_unit) {
    const uint8_t* cur = code_unit->;
    uint8_t byte = *cur++;
    uint32_t value = byte & 0x7f;
    size_t shift = 7;
    while (byte >= 0x80) {
        byte = *cur++;
        value += ((uint32_t)(byte & 0x7f) << shift);
        shift += 7;
    }
    *bufp = cur;
    return value;
}

int read_next_code_unit(FILE *in, CodeUnits *code_units) {

}

int write_code_unit(FILE *out, const CodeUnit *code_unit) {

}