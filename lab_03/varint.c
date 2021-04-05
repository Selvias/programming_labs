#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>

size_t encode_varint(uint32_t value, uint8_t* buf);
uint32_t decode_varint(const uint8_t** bufp);
uint32_t generate_number();

int main () {

    uint8_t* buffer = NULL;//Выделить память
    buffer = (uint8_t*)malloc(4*sizeof(uint8_t)); //Вызов генерации числа
    FILE *out_uncompressed;    //Запись в файл с учётом использованного количества байт (Возвращаемое кодировщиком значение)
    FILE *out_compressed;
    out_uncompressed = fopen("uncompressed.dat", "w");
    out_compressed = fopen("compressed.dat", "w");

    uint32_t digit = 0;

    for (int i = 0; i < 1000000; i++) {
        fprintf(out_uncompressed, "%d\n", digit = generate_number());

        int used_byte = encode_varint(digit, buffer);
        printf("BYTES : %d\n", used_byte);

        fprintf(out_compressed, "%d\n", *buffer);

    }

    fclose(out_uncompressed);
    fclose(out_compressed);

    return 0;
}

size_t encode_varint(uint32_t value, uint8_t* buf)
{
    assert(buf != NULL);
    uint8_t* cur = buf;                    //     |1....2....3....4....|....
    while (value >= 0x80) {                                          //
        const uint8_t byte = (value & 0x7f) | 0x80;                 //      11010101 10101010  Формирование порядка Little Endian             
        *cur = byte;                                               //
        value >>= 7;                                              //      00000000 00000011
        ++cur;                                                   //                10101011
    }                                                           //                 10000000
    *cur = value;                                              //                  10101010 10101011 00000011
    ++cur;                                                    //
    return cur - buf;                                        //  return Количество байт под закодированное число
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