#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    char character; /** The character of the node */
    int frequency;  /** The number of occurence (frequency) of the character in the file */
    int depth;      /** The depth of the node in the tree represent the number of bits the character is encoded with */
    int code;       /** The code of the node */

    struct Node *left;  /** The left child of the node */
    struct Node *right; /** The right child of the node */
} Node;

/**
 * @brief Create a node object
 *
 * @param character - the character of the node
 * @param frequency - the frequency of the character
 * @param depth - the depth of the node
 * @param code - the code of the node
 * @return Node*
 */
Node *create_node(char character, int frequency, int depth, int code);

/**
 * @brief Create a leaf object
 *
 * @param character - the character of the node
 * @param frequency - the frequency of the character
 * @return Node*
 */
Node *create_leaf(char character, int frequency);

/**
 * @brief Create a parent object
 *
 * @param left - the left child of the node
 * @param right - the right child of the node
 * @return Node*
 */
void insert_right_node(Node *parent, Node *right);

/**
 * @brief Create a parent object
 *
 * @param left - the left child of the node
 * @param right - the right child of the node
 * @return Node*
 */
void insert_left_node(Node *parent, Node *left);

/**
 * @brief Create a parent object
 *
 * @param left - the left child of the node
 * @param right - the right child of the node
 * @return Node*
 */
void find_two_smallest(Node *nodes[], int size, int *smallest, int *second_smallest);

/**
 * @brief Create a parent object
 *
 * @param left - the left child of the node
 * @param right - the right child of the node
 * @return Node*
 */
void print_node(Node *node);

#endif