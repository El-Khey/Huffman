#ifndef _HUUFMAN_TREE_H_
#define _HUUFMAN_TREE_H_

#include <stdio.h>
#include <stdlib.h>

#include "../../../../constants.h"
#include "node.h"

/**
 * @brief Create a huffman tree
 *
 * @param leaves_nodes - the array of leaves nodes
 * @return Node* - the root of the huffman tree
 */
Node *create_huffman_tree(Node **leaves_nodes);

/**
 * @brief Create the huffman codes for each leaf
 *
 * @param root - the root of the huffman tree
 */
void create_codes(Node *node);

/**
 * @brief Initialize the huffman leaves nodes
 * by storing the characters and their frequencies into an array of nodes
 *
 * @param nodes - the array of nodes
 * @param tab - the array of frequencies
 */
void initialize_huffman_nodes(Node **nodes, int *tab);

/**
 * @brief Print the huffman tree
 *
 * @param root - the root of the huffman tree
 */
void print_tree(Node *root);

/**
 * @brief Print the huffman codes
 *
 * @param root - the root of the huffman tree
 */
void print_codes(Node *root);

#endif