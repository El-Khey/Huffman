#include <stdio.h>
#include <stdlib.h>

#include "./binary_tree/binary_tree.h"

#define MAX_SIZE 100
#define MAX_CHAR 256

void read_partial_content(const char *filename)
{
    FILE *file;
    char content[MAX_SIZE];
    int read_size;

    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        exit(1);
    }

    /** Reading up to 1000 bytes from the file using fread */
    read_size = fread(content, 1, MAX_SIZE, file);

    if (read_size > 0)
    {
        printf("Partial file content (using fread):\n");
        /** Displaying the content read using fread */
        fwrite(content, 1, read_size, stdout);
    }
    else
    {
        printf("The file is empty or an error occurred while reading.\n");
    }

    fclose(file);
}

void read_full_content(const char *filename)
{
    FILE *file;
    char ch;

    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        exit(1);
    }

    printf("\n-----------------------------------\n");
    printf("\nFull file content (using fgetc):\n");
    /** Reading and displaying the content of the file using fgetc until EOF */
    while ((ch = fgetc(file)) != EOF)
    {
        putchar(ch);
    }

    fclose(file);
}

void occurrence(FILE *file, int tab[MAX_CHAR])
{
    int ch;
    int i;

    /** Initialize the array with zeros */
    for (i = 0; i < MAX_CHAR; i++)
    {
        tab[i] = 0;
    }

    /** Count occurrences of each character */
    while ((ch = fgetc(file)) != EOF)
    {
        tab[ch]++;
    }
}

void display_occurrence(int tab[MAX_CHAR])
{
    int i;

    printf("\n-----------------------------------\n");
    printf("\nOccurrences of each character:\n");
    for (i = 0; i < MAX_CHAR; i++)
    {
        if (tab[i] > 0)
        {
            printf("'%c' (ASCII: %d) : %d\n", i, i, tab[i]);
        }
    }

    printf("\n-----------------------------------\n");

    printf("\n");

    printf("The number of characters in the file is: %d\n", i);
    printf("\n-----------------------------------\n");

    printf("\n");
}

void print_tree_helper(Node *root, int level)
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

        new_node = create_node('\0', leaves_nodes[smallest]->frequency + leaves_nodes[second_smallest]->frequency, 0, 0);

        insert_left_node(new_node, leaves_nodes[smallest]);
        insert_right_node(new_node, leaves_nodes[second_smallest]);

        leaves_nodes[smallest] = new_node;
        leaves_nodes[second_smallest] = NULL;

        index_smallest = smallest;
    }

    return leaves_nodes[index_smallest];
}

void init_huffman_nodes(Node *nodes[], int tab[MAX_CHAR], int size)
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

int main()
{
    char filename[100];
    int tab[MAX_CHAR];
    int success;

    FILE *file;
    Node *leaves_nodes[MAX_CHAR];
    Node *huffman_tree;

    printf("Enter the name of the file to open: ");
    success = scanf("%s", filename);

    if (success != 1)
    {
        printf("Invalid input. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    /**
        read_partial_content(filename);
        read_full_content(filename);
    */

    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        exit(EXIT_FAILURE);
    }

    occurrence(file, tab);
    display_occurrence(tab);

    init_huffman_nodes(leaves_nodes, tab, MAX_CHAR);
    printf("Huffman nodes initialized.\n");

    huffman_tree = create_huffman_tree(leaves_nodes, MAX_CHAR);
    printf("Huffman tree created.\n");

    print_tree(huffman_tree);

    fclose(file);
    exit(EXIT_SUCCESS);
}
