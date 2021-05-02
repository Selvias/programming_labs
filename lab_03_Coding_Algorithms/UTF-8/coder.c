#include "coder.h"
#include "command.h"

int encode (uint32_t code_point, CodeUnit *code_unit) {

    assert(code_unit->code != NULL);

    if (code_point < ONEB) {
        // 1 Байт, "как есть"
        code_unit->code[0] = (uint8_t)(code_point & 0x7f);
        code_unit->length = 1;
        return 0;
    }
    else if (code_point >= ONEB && code_point < 2048) {
        // 2 Байта
        const uint8_t byte = (code_point & 0x3f) | 0x80;
        code_unit->code[1] = byte;
        code_point >>= 6;

        code_unit->code[0] = (code_point & 0x1f) | TWOB;

        code_point >>=5;
        code_unit->length = 2;
        return 0;
    }
    else if (code_point >= 2048 && code_point < 65536) {
        //3 Байта
        const uint8_t byte = (code_point & 0x3f) | 0x80;
        code_unit->code[2] = byte;
        code_point >>= 6;

        code_unit->code[1] = (code_point & 0x3f) | 0x80;
        code_point >>= 6;

        code_unit->code[0] = (code_point & 0xf) | THREEB;
        code_point >>=4;

        code_unit->length = 3;
        return 0;
    }
    else if (code_point >= 65536 && code_point < 2097152) {
        //4 Байта
        const uint8_t byte = (code_point & 0x3f) | 0x80;
        code_unit->code[3] = byte;
        code_point >>= 6;

        code_unit->code[2] = (code_point & 0x3f) | 0x80;
        code_point >>= 6;

        code_unit->code[1] = (code_point & 0x3f) | 0x80;
        code_point >>= 6;

        code_unit->code[0] = (code_point & 0x7) | FOURB;
        code_point >>=3;

        code_unit->length = 4;
        return 0;
    }
    return -1;
}

uint32_t decode (const CodeUnit *code_unit) {

    uint32_t cont = 0;

    if (*code_unit->code < ONEB) {
        cont = (uint32_t)code_unit->code[0];
    }
    else if (*code_unit->code >= ONEB && *code_unit->code < THREEB) {
        cont += ((uint32_t)(code_unit->code[0] & 0x1f) << 6);
        cont += ((uint32_t)(code_unit->code[1] & 0x3f)); 
    } 
    else if (*code_unit->code >= THREEB && *code_unit->code < FOURB) {
        cont += ((uint32_t)(code_unit->code[0] & 0xf) << 12);
        cont += ((uint32_t)(code_unit->code[1] & 0x3f) << 6);
        cont += ((uint32_t)(code_unit->code[2] & 0x3f)); 
    }
    else if (*code_unit->code >= FOURB && *code_unit->code <= LIM) {
        cont += ((uint32_t)(code_unit->code[0] & 0x7) << 18);
        cont += ((uint32_t)(code_unit->code[1] & 0x3f) << 12);
        cont += ((uint32_t)(code_unit->code[2] & 0x3f) << 6);
        cont += ((uint32_t)(code_unit->code[3] & 0x3f)); 
    }
    return cont;
}

int read_next_code_unit (FILE *in, CodeUnit *code_unit) {

    uint8_t *temp = (uint8_t*)malloc(sizeof(uint8_t));
    if (temp == NULL)
        return -1;

    fread(temp, 1, 1, in);

    if (*temp < ONEB) {
        code_unit->code[0] = *temp;
        code_unit->length = 1;
        return 0;
    }
    else if (*temp >= ONEB && *temp < THREEB) {
        code_unit->length = 2;
        code_unit->code[0] = *temp;
        fread(code_unit->code + 1, 1, code_unit->length - 1, in);
        return 0;
    } 
    else if (*temp >= THREEB && *temp < FOURB) {
        code_unit->length = 3;
        code_unit->code[0] = *temp;
        fread(code_unit->code + 1, 1, code_unit->length - 1, in);
        return 0;
    }
    else if (*temp >= FOURB && *temp <= LIM) {
        code_unit->length = 4;
        code_unit->code[0] = *temp;
        fread(code_unit->code + 1, 1, code_unit->length - 1, in);
        return 0;
    }
    return -1;
}

int write_code_unit (FILE *out, const CodeUnit *code_unit) {
    fwrite(&code_unit->code, 1, code_unit->length, out);
    return 0;
}