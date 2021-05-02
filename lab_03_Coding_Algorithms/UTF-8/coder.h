#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

enum {
    MaxCodeLength = 4,
    ONEB = 0x80,
    TWOB = 0xC0,
    THREEB = 0xE0,
    FOURB = 0xF0,
    ADDB = 0x80,
    LIM = 0xF7
};

typedef struct {
    uint8_t code[MaxCodeLength];
    size_t length;
} CodeUnit;

int encode (uint32_t code_point, CodeUnit *code_unit);
uint32_t decode (const CodeUnit *code_unit);
int read_next_code_unit (FILE *in, CodeUnit *code_unit);
int write_code_unit (FILE *out, const CodeUnit *code_unit);