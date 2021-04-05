#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>

size_t encode_varint(uint32_t value, uint8_t* buf);
uint32_t decode_varint(const uint8_t** bufp);
uint32_t generate_number();

int main () {

    uint8_t* buffer = NULL;                                             //Выделить память
    // buffer = (uint8_t*)malloc(4*sizeof(uint8_t)); 
    buffer = (uint8_t*)malloc(sizeof(uint8_t)); 
    FILE *out_uncompressed;    
    FILE *out_compressed;
    FILE *out_decompressed;

    out_uncompressed = fopen("uncompressed.dat", "w");
    out_compressed = fopen("compressed.dat", "w");

    uint32_t digit = 0;

    for (int i = 0; i < 1000000; i++) {
        fprintf(out_uncompressed, "%d\n", digit = generate_number());   //Вызов генерации числа 
                                                                        //Кодировка работает некорректно с числами, использующими более чем один байт для своего представления
        encode_varint(digit, buffer);

        fprintf(out_compressed, "%d\n", *buffer);                       //Запись в файл с учётом использованного количества байт (Возвращаемое кодировщиком значение)

    }

    fclose(out_uncompressed);
    fclose(out_compressed);

    out_compressed = fopen("compressed.dat", "r");
    out_decompressed = fopen("decompressed.dat", "w");

    // const uint8_t **val = (const uint8_t**)malloc(sizeof(uint8_t*));

    for (int i = 0; i < 1000000; i++) {

        const uint8_t *val = (uint8_t*)malloc(4*sizeof(uint8_t));
        fscanf(out_compressed, "%d", val);
        // printf("%d", val[0]);
        uint32_t uncode = decode_varint(&val);
        fprintf(out_decompressed, "%u\n", uncode);
    }

    fclose(out_compressed);
    fclose(out_decompressed);

    return 0;
}

size_t encode_varint(uint32_t value, uint8_t* buf)
{
    assert(buf != NULL);
    uint8_t* cur = buf;                                               //    |1....2....3....4....|....
    while (value >= 0x80) {                                          //
        const uint8_t byte = (value & 0x7f) | 0x80;                 //      11010101 10101010  Формирование порядка Little Endian             
        *cur = byte;                                               //
        value >>= 7;                                              //        00000000 00000011
        ++cur;                                                   //                  10101011
    }                                                           //                   10000000
    *cur = value;                                              //                    10101010 10101011 00000011
    ++cur;                                                    //
    buf = (uint8_t*)realloc(buf, (cur - buf)*(sizeof(uint8_t)));
    return cur - buf;                                        //             return Количество байт под закодированное число
}

uint32_t decode_varint(const uint8_t** bufp)
{
    const uint8_t* cur = *bufp;
    uint8_t byte = *cur++;
    uint32_t value = byte & 0x7f;
    size_t shift = 7;
    while (byte >= 0x80) {
        byte = *cur++;
        value += (byte & 0x7f) << shift;
        shift += 7;
    }
    *bufp = cur;
    return value;
}

/*
 * Диапазон             Вероятность
 * -------------------- -----------
 * [0; 128)             90%
 * [128; 16384)         5%
 * [16384; 2097152)     4%
 * [2097152; 268435455) 1%
 */

uint32_t generate_number()
{
    const int r = rand();
    const int p = r % 100;
    if (p < 90) {
        return r % 128;
    }
    if (p < 95) {
        return r % 16384;
    }
    if (p < 99) {
        return r % 2097152;
    }
    return r % 268435455;
}