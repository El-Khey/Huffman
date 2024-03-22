#include <stdio.h>
#include <stdlib.h>

#include "./tree/huffman_tree.h"
#include "./utils/utils.h"
#include "./compression/compression.h"

#define MAX_CHAR 256

int main()
{
    char filename[100];
    int success;

    printf("Enter the name of the file to open: ");
    success = scanf("%s", filename);

    if (!success)
    {
        printf("Invalid input. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    compress_file(filename, "compressed.txt");

    /**
        read_partial_content(filename);
        read_full_content(filename);
    */

    exit(EXIT_SUCCESS);
}
