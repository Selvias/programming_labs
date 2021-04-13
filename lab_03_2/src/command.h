#pragma once
#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>

int encode_file(const char *in_file_name, const char *out_file_name);
int decode_file(const char *in_file_name, const char *out_file_name);
