#include "alphabet.h"

static void populate_alphabet(Node *node, Node *alphabet[])
{
    if (node == NULL)
    {
        return;
    }

    if (is_leaf(node))
    {
        alphabet[node->ascii] = node;
    }

    populate_alphabet(node->left, alphabet);
    populate_alphabet(node->right, alphabet);
}

void compute_alphabet(Node *root, Node **alphabet)
{
    int i;
    for (i = 0; i < MAX_CHAR; i++)
    {
        alphabet[i] = NULL;
    }

    populate_alphabet(root, alphabet);
}

void print_alphabet(Node **alphabet)
{
    int i;

    printf("+------+----------+-------+------------------+\n");
    printf("| ASCII| Frequency| Depth |       Code       |\n");
    printf("+------+----------+-------+------------------+\n");

    for (i = 0; i < MAX_CHAR; i++)
    {
        if (alphabet[i] != NULL)
        {
            printf("|  %3d |   %6d |   %2d  | ", alphabet[i]->ascii, alphabet[i]->frequency, alphabet[i]->depth);
            print_code(alphabet[i]->depth, alphabet[i]->code);
            printf(" \n");
        }
    }
    printf("+------+----------+-------+------------------+\n");
}