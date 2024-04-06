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
