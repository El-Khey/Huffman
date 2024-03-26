#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>

#include "./utils/utils.h"
#include "./tree/huffman_tree.h"
#include "./compression/compression.h"
#include "./decompression/decompression.h"

static void usage()
{
    printf("\nUsage: huffman [options]\n\n");

    printf("Options:\n");
    printf("  -c <output_file> <input_file/directories> : Compress files/directories\n");
    printf("  -d <input_file> [output_directory]        : Decompress file to optional directory\n");
    printf("  -h                                        : Display help\n\n");

    printf("Example usages:\n");
    printf("  Compress a file:     huffman -c compressed.bin input.txt\n");
    printf("  Compress a directory: huffman -c compressed.bin directory/\n");
    printf("  Decompress a file:   huffman -d compressed.bin\n\n");

    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int opt;
    char *output_file = NULL;
    char *input_file = NULL;
    char *output_directory = NULL;

    while ((opt = getopt(argc, argv, "c:d:h")) != -1)
    {
        switch (opt)
        {
        case 'c':
            output_file = optarg;
            input_file = argv[optind];
            break;
        case 'd':
            input_file = optarg;
            output_directory = (optind < argc) ? argv[optind] : "./";
            break;
        case 'h':
            usage();
            break;
        default:
            fprintf(stderr, "\n----------------------------\n");
            fprintf(stderr, "/!\\ Unknown option: %c /!\\", optopt);
            fprintf(stderr, "\n----------------------------\n");
            usage();
            break;
        }
    }

    if (output_file != NULL && input_file != NULL)
    {
        compress_file(output_file, input_file);
    }
    else if (input_file != NULL)
    {
        decompress_file(input_file, output_directory);
    }
    else
    {
        fprintf(stderr, "\n--------------------------------------\n");
        fprintf(stderr, "/!\\ No valid options provided. /!\\");
        fprintf(stderr, "\n--------------------------------------\n");
        usage();
    }

    exit(EXIT_SUCCESS);
}
