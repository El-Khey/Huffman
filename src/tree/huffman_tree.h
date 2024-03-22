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
 * @param size - the size of the array
 */
void initialize_huffman_nodes(Node *nodes[], int tab[MAX_CHAR], int size);

/**
 * @brief Compute the alphabet by traversing the huffman tree and
 * storing the leaves nodes into an array of nodes
 *
 * @param root - the root of the huffman tree
 * @param alphabet - the array of nodes
 */
void compute_alphabet(Node *root, Node *alphabet[]);

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