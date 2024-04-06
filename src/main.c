#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "./utils/utils.h"
#include "./tree/huffman_tree.h"
#include "./compression/compression.h"
#include "./decompression/decompression.h"

static void usage()
{
    printf("\nUsage: huffman [options]\n\n");

    printf("Options:\n");
    printf("  -c <archive_name> <input_file/directories> : Compress files/directories\n");
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
    char *archive_name = NULL;
    char **input_files = NULL;
    char *output_directory = NULL;
    int num_files = 0, i = 0;

    while ((opt = getopt(argc, argv, "c:d:h")) != -1)
    {
        switch (opt)
        {
        case 'c':
            num_files = argc - optind;
            input_files = malloc(num_files * sizeof(char *));

            for (; i < num_files; i++)
            {
                input_files[i] = argv[optind + i];
            }

            archive_name = optarg;
            break;

        case 'd':
            archive_name = optarg;
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

    if (archive_name != NULL && input_files != NULL && num_files > 0)
    {
        compress_files(input_files, archive_name, num_files);
    }
    else if (archive_name != NULL)
    {
        decompress_file(archive_name, output_directory);
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
