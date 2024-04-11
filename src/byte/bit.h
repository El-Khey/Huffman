#ifndef _BIT_H_
#define _BIT_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Construct a byte to store the bits. and write the byte to the file if it is full.
 *
 * @param file - the file to write the byte to
 * @param byte - the byte to store the bits
 * @param bit_position - the position of the bit in the byte
 * @param bit - the bit to write
 */
void write_bit(FILE *file, uint8_t *byte, uint8_t *bit_position, uint8_t bit);

/**
 * @brief Write the remaining bits in the byte to the file.
 *
 * @param file - the file to write the byte to
 * @param byte - the byte to store the bits
 * @param bit_position - the position of the bit in the byte
 */
void flush_bits(FILE *file, uint8_t *byte, uint8_t *bit_position);

/**
 * @brief Read a bit from the file.
 *
 * @param file - the file to read the bit from
 * @param byte - the byte to store the bits
 * @param bit_position - the position of the bit in the byte
 * @return int - the bit read from the file
 */
int read_bit(FILE *file, uint8_t *byte, uint8_t *bit_position);

#endif