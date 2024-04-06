#include "huffman_tree.h"

static void update_depth(Node *root, int depth)
{
    if (root == NULL)
    {
        return;
    }

    root->depth = depth;

    update_depth(root->left, depth + 1);
    update_depth(root->right, depth + 1);
}

Node *create_huffman_tree(Node **leaves_nodes)
{
    int index_smallest = -1;
    Node *new_node;

    while (1)
    {
        int smallest, second_smallest;
        find_two_smallest(leaves_nodes, MAX_CHAR, &smallest, &second_smallest);

        if (second_smallest == -1 || smallest == -1)
        {
            break;
        }

        new_node = create_node('\0', leaves_nodes[smallest]->frequency + leaves_nodes[second_smallest]->frequency, 0, 0);

        insert_left_node(new_node, leaves_nodes[smallest]);
        insert_right_node(new_node, leaves_nodes[second_smallest]);

        leaves_nodes[smallest] = new_node;
        leaves_nodes[second_smallest] = NULL;

        index_smallest = smallest;
    }

    update_depth(leaves_nodes[index_smallest], 0);
    return leaves_nodes[index_smallest];
}

void initialize_huffman_nodes(Node **nodes, int *tab)
{
    int i;

    for (i = 0; i < MAX_CHAR; i++)
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

static void create_codes_helper(Node *node, int *code, int depth)
{
    if (is_leaf(node))
    {
        int i;

        node->code = (int *)malloc(sizeof(int) * depth);
        for (i = 0; i < depth; i++)
        {
            node->code[i] = code[i];
        }
    }
    else
    {
        code[depth] = 1;
        create_codes_helper(node->left, code, depth + 1);

        code[depth] = 0;
        create_codes_helper(node->right, code, depth + 1);
    }
}

void create_codes(Node *node)
{
    int code[MAX_CHAR];
    create_codes_helper(node, code, 0);
}

void print_tree_helper(Node *root, char side)
{
    if (root == NULL)
    {
        return;
    }

    printf("%*s", root->depth * 4, "");

    if (side != '\0')
    {
        printf("%c--", side);
    }

    if (root->ascii == '\0')
    {
        printf("[Freq: %d]\n", root->frequency);
    }
    else
    {
        printf("'%c' (Freq: %d)\n", root->ascii, root->frequency);
    }

    print_tree_helper(root->left, 'L');
    print_tree_helper(root->right, 'R');
}

void print_tree(Node *root)
{
    printf("Huffman Tree:\n");
    print_tree_helper(root, '\0');
}

static void print_row(int ascii, int *code, int depth)
{
    printf("|    '%c'    |  %3d  | ", ascii, ascii);
    print_code(depth, code);
    printf("\n");
}

static void print_codes_helper(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    if (is_leaf(root))
    {
        print_row(root->ascii, root->code, root->depth);
    }

    print_codes_helper(root->left);
    print_codes_helper(root->right);
}

void print_codes(Node *root)
{
    printf("| Character | ASCII | Code |\n");
    printf("|-----------|-------|------|\n");
    print_codes_helper(root);
}
