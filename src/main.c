#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "./huffman/utils/utils.h"
#include "./huffman/codec/coding/tree/huffman_tree.h"
#include "./huffman/codec/compression/compression.h"
#include "./huffman/codec/decompression/decompression.h"
#include "./gui/gui.h"

static void usage()
{
    printf("\nUsage: huffman [options]\n\n");

    printf("Options:\n");
    printf("  -c <archive_name> <input_files/directories> : Compress files/directories\n");
    printf("  -d <input_file> [output_directory]        : Decompress file to optional directory\n");
    printf("  -m                                        : Launch the graphical interface\n");
    printf("  -h                                        : Display help\n\n");

    printf("Example usages:\n");
    printf("  Compress a file:     huffman -c compressed.bin input.txt\n");
    printf("  Compress a directory: huffman -c compressed.bin directory/\n");
    printf("  Decompress a file:   huffman -d compressed.bin\n\n");

    exit(EXIT_FAILURE);
}

static void compute_type(char *path, Type *type)
{
    if (is_text_file(path))
    {
        if (*type == FOLDER_TYPE)
        {
            *type = BOTH_TYPE;
        }
        else
        {
            *type = FILE_TYPE;
        }
    }
    else
    {
        if (*type == FILE_TYPE)
        {
            *type = BOTH_TYPE;
        }
        else
        {
            *type = FOLDER_TYPE;
        }
    }
}

int main(int argc, char *argv[])
{
    char *output_directory = NULL;
    char *archive_name = NULL;
    char **input_files = NULL;
    int num_files = 0, i = 0;
    int opt;

    Type compression_type = NONE_TYPE;
    Action action = NOTHING;
    int launch_gui = 0;

    while ((opt = getopt(argc, argv, "c:d:h:m")) != -1)
    {
        switch (opt)
        {
        case 'c':
            archive_name = optarg;
            action = COMPRESS;

            num_files = argc - optind;
            input_files = malloc(num_files * sizeof(char *));

            for (i = 0; i < num_files; i++)
            {
                input_files[i] = argv[optind + i];
                compute_type(input_files[i], &compression_type);
            }
            break;

        case 'd':
            archive_name = optarg;
            output_directory = (optind < argc) ? argv[optind] : "./";
            action = DECOMPRESS;
            printf("Output directory: %s\n", output_directory);
            break;

        case 'm':
            launch_gui = 1;
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

    if (launch_gui)
    {
        launch_graphical_interface();
    }
    else
    {
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
            printf("Decompressing...\n");
            printf("output_directory: %s\n", output_directory);
            decompress(archive_name, output_directory);
        }
    }

    exit(EXIT_SUCCESS);
}
