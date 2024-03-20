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

typedef struct HuffmanTree
{
    Node *root;
} HuffmanTree; 

Node *create_node(char character, int frequency, int depth, int code);

/** int *tab, int index */
Node *create_leaf(char character, int frequency);

void insert_right_node(Node *parent, Node *right);

void insert_left_node(Node *parent, Node *left);

void find_two_smallest(Node *nodes[], int size, int *smallest, int *second_smallest);

void display_node(Node *node);

#endif