#include <stdio.h>
#include <stdlib.h>

#include "./tree/huffman_tree.h"
#include "./utils/utils.h"

#define MAX_CHAR 256

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

    count_char_frequencies(file, tab);
    display_char_frequencies(tab);

    initialize_huffman_nodes(leaves_nodes, tab, MAX_CHAR);
    printf("Huffman nodes initialized.\n");

    huffman_tree = create_huffman_tree(leaves_nodes, MAX_CHAR);
    printf("Huffman tree created.\n");

    print_tree(huffman_tree);

    fclose(file);
    exit(EXIT_SUCCESS);
}
