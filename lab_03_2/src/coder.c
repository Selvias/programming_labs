#include "coder.h"

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
    return value;
}

int encode(uint32_t code_point, CodeUnits *code_units) {
    assert((code_units != NULL) && (code_units->code != NULL));
    uint8_t* cur = code_units->code; 
                                  
    while (code_point >= 0x80) {                      
        const uint8_t byte = (code_point & 0x7f) | 0x80;                         
        *cur = byte;                                              
        code_point >>= 7;                                             
        ++cur;                                                   
    }             
    *cur = code_point;                                
    ++cur;

    code_units->length = cur - code_units->code;  

    if (code_units != NULL && code_units->length != 0)
        return 0;
    else 
        return -1;
}

uint32_t decode(const CodeUnit *code_unit) {
    // Value *vale = (Value *)malloc(sizeof(Value));

    const uint8_t* cur = (const uint8_t*)code_unit->code;
    uint8_t byte = *cur++;
    uint32_t value = byte & 0x7f;
    size_t shift = 7;
    while (byte >= 0x80) {
        byte = *cur++;
        value += ((uint32_t)(byte & 0x7f) << shift);
        shift += 7;
    }
    *code_unit->code = cur;
    vault.val = value;
    return 0;
}

int read_next_code_unit(FILE *in, CodeUnits *code_units) {

    int j = 0;

    do {
        fread(&code_units->code[j], 1, 1, in);
        if (code_units->code[j] < 0x80) {
            printf("BYTES : %d\n", (j + 1));
            printf("VALUE : %d\n", code_units->code[j]);
            break;
        }
        j++;
    } while (code_units->code[j - 1] >= 0x80);
    
    return 0;
}

int write_code_unit(FILE *out, const CodeUnit *code_unit) {

    fprintf(out, "%d", vault.val);
    return 0;
}