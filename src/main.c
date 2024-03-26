#include <stdio.h>
#include <stdlib.h>

#include "./tree/huffman_tree.h"
#include "./utils/utils.h"
#include "./compression/compression.h"
#include "./decompression/decompression.h"

#define MAX_CHAR 256

int main(int argc, char *argv[])
{
    int action = 1;
    if (argc != 2)
    {
        printf("Usage: %s <integer>\n", argv[0]);
        printf("<integer> : <1> to compress a file\n");
        printf("<integer> : <2> to decompress a file\n");
        exit(EXIT_FAILURE);
    }

    action = atoi(argv[1]);

    if (action == 1)
    {
        compress_file("example/medium/medium", "example/medium/compressed_medium.bin");
    }
    else if (action == 2)
    {
        decompress_file("example/medium/compressed_medium.bin", "example/medium/decompressed_medium");
    }
    else
    {
        printf("Invalid action.\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
