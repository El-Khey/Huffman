#include "./node.h"

Node *create_node(int ascii, int frequency, int depth, int code)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->ascii = ascii;
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

Node *create_leaf(int ascii, int frequency)
{
    return create_node(ascii, frequency, 0, 0);
}

int is_leaf(Node *node)
{
    return node->left == NULL && node->right == NULL;
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

int get_number_of_leaves(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    if (is_leaf(root))
    {
        return 1;
    }

    return get_number_of_leaves(root->left) + get_number_of_leaves(root->right);
}

void print_node(Node *node)
{
    if (node != NULL)
    {
        printf("Character: '%c', Frequency: %d, Depth: %d, Code: %d\n", node->ascii, node->frequency, node->depth, node->code);
    }
}