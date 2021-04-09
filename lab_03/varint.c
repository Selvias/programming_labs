#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>

size_t encode_varint(uint32_t value, uint8_t* buf);
uint32_t decode_varint(const uint8_t** bufp);
uint32_t generate_number();

int main () {

    int array[100] = {0};

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
        array[i] = sz;

        fwrite(buffer, 1, sz, out_compressed);
    }

    fclose(out_uncompressed);
    fclose(out_compressed);

    out_compressed = fopen("compressed.dat", "r");
    out_decompressed = fopen("decompressed.dat", "w");


    for (int i = 0; i < 100; i++) {
        uint8_t **val = (uint8_t**)malloc(sizeof(uint8_t*));
        *val = (uint8_t*)calloc(4, sizeof(uint8_t));

        fread(*val, 1, array[i], out_compressed);

        const uint8_t **val_cp = (const uint8_t**)val;

        uint32_t uncode = decode_varint(val_cp);
        fprintf(out_decompressed, "%u\n", uncode);
    }

    fclose(out_compressed);
    fclose(out_decompressed);

    free(buffer);
    return 0;
}

size_t encode_varint(uint32_t value, uint8_t* buf)
{
    assert(buf != NULL);
    uint8_t* cur = buf; 
                                  
    while (value >= 0x80) {                      
        const uint8_t byte = (value & 0x7f) | 0x80;                         
        *cur = byte;                                              
        value >>= 7;                                             
        ++cur;                                                   
    }             
    *cur = value;                                
    ++cur;                                               
    return cur - buf;                                        
}

uint32_t decode_varint(const uint8_t** bufp)
{
    const uint8_t* cur = *bufp;                             //Указатель на область в памяти, где хранится считанное скомпрессированное число (первый байт)
    uint8_t byte = *cur++;                                  //Переменной присваивается адрес текущего считываемого байта, затем указатель на область в памяти сдвигается на 1
    uint32_t value = byte & 0x7f;                           //Побитовое и числа и 01111111
    size_t shift = 7;                                       //Переменная сдвига на 7 бит (для того, чтобы вернуть исходный порядок байт)
    while (byte >= 0x80) {                                  //Пока число (байт) больше либо равно 128 (если число занимает 1 байт, то цикл не выполняется
        byte = *cur++;
        value += ((uint32_t)(byte & 0x7f) << shift);
        shift += 7;
    }
    *bufp = cur;
    // printf("VAL : %d\n", value);
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