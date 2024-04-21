#include "bit.h"

void write_bit(FILE *file, uint8_t *byte, uint8_t *bit_position, uint8_t bit)
{
    *byte = (*byte << 1) | bit;
    (*bit_position)++;

    if (*bit_position == 8)
    {
        fwrite(byte, sizeof(uint8_t), 1, file);
        *byte = 0;
        *bit_position = 0;
    }
}

void flush_bits(FILE *file, uint8_t *byte, uint8_t *bit_position)
{
    if (*bit_position > 0)
    {
        *byte <<= (8 - *bit_position);
        fwrite(byte, sizeof(uint8_t), 1, file);
    }
}

int read_bit(FILE *file, uint8_t *byte, uint8_t *bit_position)
{
    int bit;

    if (*bit_position == 0)
    {
        if (fread(byte, sizeof(uint8_t), 1, file) != 1)
        {
            return -1;
        }

        *bit_position = 8;
    }

    bit = (*byte >> (*bit_position - 1)) & 1;
    (*bit_position)--;

    return bit;
}

int *convert_binary_code_into_int_array(int binary_code, int length)
{
    int *code = (int *)calloc(length, sizeof(int));
    int i;

    for (i = 0; i < length; i++)
    {
        code[i] = (binary_code >> (length - i - 1)) & 1;
    }

    return code;
}

int convert_int_array_into_int(int *code, int length)
{
    int i;
    int binary_code = 0;

    for (i = 0; i < length; i++)
    {
        binary_code = (binary_code << 1) | code[i];
    }

    return binary_code;
}

void print_byte(uint8_t byte)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        printf("%d", (byte & 0x80) ? 1 : 0);
        byte <<= 1;
    }
}

void print_byte_array(int *byte, int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        printf("%d", byte[i]);
    }
}