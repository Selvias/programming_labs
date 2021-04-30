#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

size_t encode_varint(uint32_t value, uint8_t* buf);
uint32_t decode_varint(const uint8_t** bufp);
uint32_t generate_number();
void write(FILE *out, uint8_t **code_unit, short unsigned int length);

int main (int argc, char *argv[]) {

    char * cmd = argv[1];
    int n = 0; 

    if (strcmp(cmd, "code") == 0) {
        n = atoi(argv[2]);
        unsigned int len;
        uint8_t* buffer = NULL;
        buffer = (uint8_t*)malloc(4*sizeof(uint8_t));
        if (buffer == NULL)
            return -1;
        FILE *out_uc; 
        FILE *out_ced;
        out_uc = fopen("uncompressed.dat", "w");
        out_ced = fopen("compressed.dat", "w");
        int fullen = 0;

        uint32_t digit = 0;

        for (int i = 0; i < n; i++) {
            digit = generate_number();
            fprintf(out_uc, "%d\n", digit);
            len = encode_varint(digit, buffer);
            fullen = fullen + len;
            write(out_ced, &buffer, len);
        }

        printf("FULLEN : %d\n", fullen);

        fclose(out_uc);
        fclose(out_ced);
        free(buffer);
    }

    if (strcmp(cmd, "decode") == 0) {
    FILE *ocd;
    FILE *odd;
    ocd = fopen("compressed.dat", "r+b");
    odd = fopen("decompressed.dat", "w");

    uint8_t **value = (uint8_t**)calloc(1, sizeof(uint8_t*));
    if (value == NULL)
        return -1;
    *value = (uint8_t*)calloc(2000000, sizeof(uint8_t));
    if (*value == NULL)
        return -1;
    uint8_t *temp = (uint8_t*)calloc(1, sizeof(uint8_t));
    if (temp == NULL)
        return -1;

    int j, counter = 0;

    while (1) {
        j = 0;
        counter++;
        fread(temp, 1, 1, ocd);

        while (*temp >= 128) {
            (*value)[j] = *temp;
            fread(temp, 1, 1, ocd);
            j++;
            counter++;
        }

        // Прерывание перед записью в файл!
        if (feof(ocd)) {
            printf("counter : %d\n", counter);
            break;
        }

        (*value)[j] = *temp;
        const uint8_t **val_cp = (const uint8_t **) value;

        uint32_t uncode = decode_varint(val_cp);
        fprintf(odd, "%d\n", uncode);
        printf (" ADR : %p\n", *value);
    }

    fclose(ocd);
    fclose(odd);
    free(value);
    }

    if (strcmp(cmd, "compare") == 0) {
    FILE *out_uncompressed; 
    FILE *out_decompressed;
    out_uncompressed = fopen("uncompressed.dat", "r");
    out_decompressed = fopen("decompressed.dat", "r");

    uint32_t comp, dec;

    while (!feof(out_uncompressed) && !feof(out_decompressed)) {
        fscanf(out_uncompressed, "%d", &comp);
        fscanf(out_decompressed, "%d", &dec);
        if (comp != dec) {
            printf("Something wents wrong...\n");
            return -1;
        }
    }
    fclose(out_uncompressed);
    fclose(out_decompressed);
    }

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
    const uint8_t* cur = *bufp;
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

void write(FILE *out, uint8_t **code_unit, short unsigned int length) {
    fwrite(*code_unit, 1, length, out);
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

/*
    encode : 

    val : 00011001 01101110 10001101

    cur : 10001101

    val : 0000000 00011001 01101110 1

    cur : 10001101 11011101

    val : 0000000 0000000 00011001 01

    cur : 10001101 11011101 01100101

    decode : 

    *bufp : 10001101 11011101 01100101    

    0) cur : 10001101

    byte 10001101

    1) cur : 11011101

    0) value : 0001101

    WHILE

    byte : 11011101

    2) cur : 01100101 

    value : 0001101 + 1011101 0000000 -> 1011101 0001101

    byte  01100101

    3) cur : rubbish

    value : 1011101 0001101 + 1100101 0000000 0000000

*/