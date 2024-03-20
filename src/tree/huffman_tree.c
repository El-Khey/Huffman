#include "huffman_tree.h"

Node *create_huffman_tree(Node *leaves_nodes[], int size)
{
    int index_smallest = -1;
    Node *new_node;

    while (1)
    {
        int smallest, second_smallest;
        find_two_smallest(leaves_nodes, size, &smallest, &second_smallest);

        if (second_smallest == -1)
        {
            break;
        }

        /** TODO: compute the depth of the node and update it */
        new_node = create_node('\0', leaves_nodes[smallest]->frequency + leaves_nodes[second_smallest]->frequency, 0, 0);

        insert_left_node(new_node, leaves_nodes[smallest]);
        insert_right_node(new_node, leaves_nodes[second_smallest]);

        leaves_nodes[smallest] = new_node;
        leaves_nodes[second_smallest] = NULL;

        index_smallest = smallest;
    }

    return leaves_nodes[index_smallest];
}

void initialize_huffman_nodes(Node *nodes[], int tab[MAX_CHAR], int size)
{
    int i;

    for (i = 0; i < size; i++)
    {
        if (tab[i] > 0)
        {
            nodes[i] = create_leaf(i, tab[i]);
        }
        else
        {
            nodes[i] = NULL;
        }
    }
}

static void print_tree_helper(Node *root, int level)
{
    if (root == NULL)
    {
        return;
    }

    printf("%*s", level * 4, "");
    if (root->character == '\0')
    {
        printf("[Freq: %d]\n", root->frequency);
    }
    else
    {
        printf("'%c' (Freq: %d)\n", root->character, root->frequency);
    }

    print_tree_helper(root->left, level + 1);
    print_tree_helper(root->right, level + 1);
}

void print_tree(Node *root)
{
    printf("Huffman Tree:\n");
    print_tree_helper(root, 0);
}
