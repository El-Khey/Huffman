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

/**
 * @brief Convert a string into a code.
 *
 * @param binary_code - the binary code to convert
 * @param length - the length of the binary code
 * @return int* - the code
 */
int convert_int_array_into_int(int *code, int length);

/**
 * @brief Convert a binary code into an integer array.
 *
 * @param binary_code - the binary code to convert
 * @param length - the length of the binary code
 * @return int* - the integer array
 */
int *convert_binary_code_into_int_array(int binary_code, int length);

/**
 * @brief This function print a byte
 *
 * @param byte - the byte to print
 */
void print_byte(uint8_t byte);

/**
 * @brief This function print a byte array
 *
 * @param byte - the byte to print
 * @param length - the length of the byte
 */
void print_byte_array(int *byte, int length);

#endif