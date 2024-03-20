#ifndef _HUUFMAN_TREE_H_
#define _HUUFMAN_TREE_H_

#include <stdio.h>
#include <stdlib.h>

#include "../constants.h"
#include "node.h"

/**
 * @brief Create a huffman tree
 *
 * @param leaves_nodes - the array of leaves nodes
 * @param size - the size of the array
 * @return Node* - the root of the huffman tree
 */
Node *create_huffman_tree(Node *leaves_nodes[], int size);

/**
 * @brief Initialize the huffman nodes
 *
 * @param nodes - the array of nodes
 * @param tab - the array of frequencies
 * @param size - the size of the array
 */
void initialize_huffman_nodes(Node *nodes[], int tab[MAX_CHAR], int size);

/**
 * @brief Print the huffman tree
 *
 * @param root - the root of the huffman tree
 */
void print_tree(Node *root);

#endif