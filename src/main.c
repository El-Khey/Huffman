#include <stdio.h>
#include <stdlib.h>

#include "./tree/huffman_tree.h"
#include "./utils/utils.h"
#include "./compression/compression.h"
#include "./decompression/decompression.h"

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

    decompress_file("example/compressed_small", "example/decompressed_small");
    /*

        decompress_file("example/compressed_small", "example/decompressed_small");
        read_partial_content(filename);
        read_full_content(filename);

    */

    exit(EXIT_SUCCESS);
}
