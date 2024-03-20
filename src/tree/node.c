#include "./node.h"

Node *create_node(char character, int frequency, int depth, int code)
{
    Node *node = (Node *)malloc(sizeof(Node));

    if (node == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    node->character = character;
    node->frequency = frequency;

    node->depth = depth;
    node->code = code;

    node->left = NULL;
    node->right = NULL;

    return node;
}

void insert_right_node(Node *parent, Node *right)
{
    parent->right = right;
}

void insert_left_node(Node *parent, Node *left)
{
    parent->left = left;
}

Node *create_leaf(char character, int frequency)
{
    return create_node(character, frequency, 0, 0);
}

void find_two_smallest(Node *nodes[], int size, int *smallest, int *second_smallest)
{
    int i;

    *smallest = -1;
    *second_smallest = -1;

    for (i = 0; i < size; i++)
    {
        if (nodes[i] == NULL)
        {
            continue;
        }

        if (*smallest == -1 || nodes[i]->frequency < nodes[*smallest]->frequency)
        {
            *second_smallest = *smallest;
            *smallest = i;
        }
        else if (*second_smallest == -1 || nodes[i]->frequency < nodes[*second_smallest]->frequency)
        {
            *second_smallest = i;
        }
    }
}

void print_node(Node *node)
{
    if (node != NULL)
    {
        printf("Character: '%c', Frequency: %d, Depth: %d, Code: %d\n", node->character, node->frequency, node->depth, node->code);
    }
}