#pragma once
#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>

enum {
    MaxCodeLength = 4
};

typedef struct {
    uint8_t code[MaxCodeLength];                        
    size_t length;                                      
} CodeUnits;

//code[] - Закодированные байты, в порядке от старшего к младшему
//length - Количество байт в закодированном представлении

typedef struct {
    uint8_t *decode;                        
    size_t length;  
} CodeUnit;

//Декодированные байты
//Количество байт для чтения

int encode(uint32_t code_point, CodeUnits *code_units); 
//code_point - кодируемое число 
//code_uints - рзультат кодирования

uint32_t decode(const CodeUnit *code_unit);
//code_unit – закодированное представление числа
//Return code point : результат декодирования

int read_next_code_unit(FILE *in, CodeUnits *code_units);
/*
Считывает последовательность code_units из потока in. 
Implementation note: если считываемый code_unit битый, то функция 
пропускает байты до тех пор, пока не найдет корректный лидирующий байт.

Результат:	0 в случае успеха, -1 в случае ошибки или EOF
*/

int write_code_unit(FILE *out, const CodeUnit *code_unit);
