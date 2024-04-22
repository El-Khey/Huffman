#ifndef _DECOMPRESSION_H_
#define _DECOMPRESSION_H_

#include "../coding/tree/huffman_tree.h"
#include "../coding/alphabet/alphabet.h"
#include "../../utils/folder/folder.h"
#include "../../utils/file/file.h"
#include "../../utils/byte/bit.h"
#include "../../../debug/debug.h"
#include "../../../constants.h"
#include "../../utils/utils.h"

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef struct Header
{
    int number_of_leaves;
    Node *alphabet[MAX_CHAR];
} Header;

typedef struct Content
{
    char *path;
    char *filename;

    int size;
    int flush_size;

    int *encoded_data;
    int length_encoded_data;
} Content;

typedef struct Archive
{
    Type type;
    Header header;
    Content *content;

    int number_of_files;

    FILE *file;
    const char *filename;
} Archive;

/**
 * @brief Read the header of the compressed archive.
 *
 * @param compressed_archive - the compressed archive
 */
void decompress(char *input_file, char *output_dir);

#endif