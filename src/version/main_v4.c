#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../huffman/utils/utils.h"
#include "../huffman/codec/coding/tree/huffman_tree.h"
#include "../huffman/codec/compression/compression.h"
#include "../huffman/codec/decompression/decompression.h"

static void usage()
{
    printf("\nUsage: huffman [options]\n\n");

    printf("Options:\n");
    printf("  -c <archive_name> <directory> : Compress directory\n");
    printf("  -d <input_file> [output_directory]          : Decompress archive to optional directory\n");
    printf("  -h                                          : Display help\n\n");

    printf("Example usages:\n");
    printf("  Compress a directory: huffman -c compressed.bin directory/\n");
    printf("  Decompress a file:   huffman -d compressed.bin\n\n");

    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    char *output_directory = NULL;
    char *archive_name = NULL;
    int max_files = 1;
    char **input_files = NULL;
    int num_files = 0;
    int opt;

    Type compression_type = NONE_TYPE;
    Action action = NOTHING;

    while ((opt = getopt(argc, argv, "c:d:h")) != -1)
    {
        switch (opt)
        {
        case 'c':
            archive_name = optarg;
            action = COMPRESS;

            num_files = argc - optind;
            input_files = malloc(num_files * sizeof(char *));

            if (num_files > max_files)
            {
                fprintf(stderr, "\n--------------------------------\n");
                fprintf(stderr, "<Error> Too many directory to compress\n");
                fprintf(stderr, "--------------------------------\n");
                usage();
            }

            input_files[num_files - 1] = argv[optind];
            compression_type = compute_compression_type(input_files, num_files);
            if (compression_type != FOLDER_TYPE)
            {
                fprintf(stderr, "\n-----------------------------------------------\n");
                fprintf(stderr, "<Error> Cannot compress files only one directory\n");
                fprintf(stderr, "-----------------------------------------------\n");
                usage();
            }
            break;

        case 'd':
            archive_name = optarg;
            output_directory = (optind < argc) ? argv[optind] : "./";
            action = DECOMPRESS;
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

    if (action == COMPRESS)
    {
        if (archive_name == NULL || input_files == NULL || num_files == 0)
        {
            fprintf(stderr, "\n--------------------------------------\n");
            fprintf(stderr, "/!\\ No valid options provided. /!\\");
            fprintf(stderr, "\n--------------------------------------\n");
            usage();
        }
        compress(input_files, archive_name, num_files, compression_type);
    }
    else if (archive_name != NULL && action == DECOMPRESS)
    {
        decompress(archive_name, output_directory);
    }

    exit(EXIT_SUCCESS);
}
