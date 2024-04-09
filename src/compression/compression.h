#ifndef _COMPRESSION_H_
#define _COMPRESSION_H_

#include "../decompression/decompression.h"
#include "../tree/huffman_tree.h"
#include "../tree/alphabet.h"
#include "../utils/folder.h"
#include "../debug/debug.h"
#include "../utils/utils.h"
#include "../utils/file.h"
#include "../constants.h"
#include "../byte/bit.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct File
{
    char *path;
    char *name;
    int size;

    int *encoded_data;
    int length_encoded_data;
} File;

typedef struct Files
{
    int number_of_files;
    File *files;
} Files;

typedef struct Directory
{
    char *path;
    char *name;

    Files list;
} Directory;

typedef struct Directories
{
    int number_of_directories;
    Directory *directories;
} Directories;

typedef struct Data
{
    Directories directories;
    Files files;
    Type type;
} Data;

/**
 * @brief Compress a list of files or directories.
 *
 * @param inputs - the list of files or directories
 * @param output_file - the output archive
 * @param number_of_inputs - the number of files or directories
 * @param archive_type - the type of the archive
 */
void compress(char **inputs, char *output_file, int number_of_inputs, Type archive_type);

#endif