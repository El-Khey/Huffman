#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include "../constants.h"

/**
 * @brief This function convert an integer into binary and return it as a string
 *
 * @param code - the integer to convert
 * @param size - the size of the integer
 * @return char* - the binary string
 */
char *convert_into_bits(int code, int size);

/**
 * @brief This function convert an integer into binary and return it as an array of integers
 *
 * @param code - the integer to convert
 * @param size - the size of the integer
 * @return int* - the binary array
 */
int *convert_interger_code_into_bits(int code, int size);

/**
 * @brief This function convert a binary string into an integer
 *
 * @param code - the binary string to convert
 * @param size - the size of the integer
 * @return int - the integer
 */
int convert_into_int(char *code, int size);

/**
 * @brief This function count the frequencies of each character in a file
 *
 * @param file - the file to read
 * @param tab - the array to store the frequencies
 */
void count_char_frequencies(FILE *file, int tab[MAX_CHAR]);

/**
 * @brief This function display the frequencies of each character in a file
 *
 * @param tab
 */
void display_char_frequencies(int tab[MAX_CHAR]);

#endif