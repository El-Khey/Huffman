#include "alphabet.h"

void initialize_alphabet(Node **alphabet)
{
    int i;
    for (i = 0; i < MAX_CHAR; i++)
    {
        alphabet[i] = NULL;
    }
}

static void populate_alphabet(Node *node, Node **alphabet)
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
    initialize_alphabet(alphabet);
    populate_alphabet(root, alphabet);
}

void print_alphabet(Node **alphabet)
{
    int i;

    printf("+------+----------+-------+------------------+\n");
    printf("| ASCII| Character| Frequency| Depth | Code  |\n");
    printf("+------+----------+----------+-------+-------+\n");

    for (i = 0; i < MAX_CHAR; i++)
    {
        if (alphabet[i] != NULL)
        {
            printf("|  %3d |    '%c'   |   %6d  |   %2d  | ", alphabet[i]->ascii, (char)alphabet[i]->ascii, alphabet[i]->frequency, alphabet[i]->depth);
            int *code = convert_binary_code_into_int_array(alphabet[i]->code, alphabet[i]->depth);
            print_byte_array(code, alphabet[i]->depth);
            printf(" \n");
        }
    }
    printf("+------+----------+----------+-------+-------+\n\n\n");
}