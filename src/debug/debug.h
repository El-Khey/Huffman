#ifndef DEBUG_H
#define DEBUG_H

#include "../huffman/codec/coding/alphabet/alphabet.h"
#include "../constants.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief This function activate the debug mode
 */
void activate_debug_mode();

/**
 * @brief This function check if the debug mode is activated
 *
 * @param filename - the name of the file
 * @param size - the size of the file
 * @param flush_size - the size of the flush
 */
void debug_file_size(char *filename, int size, int flush_size);

/**
 * @brief This function display the frequencies of each character in a file
 *
 * @param char_frequencies - the array of frequencies
 */
void debug_char_frequencies(int *char_frequencies);

/**
 * @brief This function display the alphabet
 *
 * @param alphabet - the array of nodes
 */
void debug_alphabet(Node **alphabet);

/**
 * @brief This function display the current extracted file
 *
 * @param filename - the name of the file
 */
void debug_current_extracted_file(char *filename);

#endif