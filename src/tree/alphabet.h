#ifndef _ALPHABET_H_
#define _ALPHABET_H_

#include "../constants.h"
#include "node.h"

/**
 * @brief This function compute the alphabet of a huffman tree
 *
 * @param root - the root of the huffman tree
 * @param alphabet - the array to store the alphabet
 */
void compute_alphabet(Node *root, Node **alphabet);

/**
 * @brief This function print the alphabet
 *
 * @param alphabet - the array to store the alphabet
 */
void print_alphabet(Node **alphabet);

#endif