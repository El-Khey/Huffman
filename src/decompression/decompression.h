#ifndef _DECOMPRESSION_H_
#define _DECOMPRESSION_H_

#include "../tree/huffman_tree.h"
#include "../tree/alphabet.h"
#include "../utils/folder.h"
#include "../utils/utils.h"
#include "../utils/file.h"
#include "../constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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
    Header header;
    Content *content;

    int number_of_files;

    FILE *file;
    const char *filename;
} Archive;

void decompress_file(char *input_file, char *output_dir);

#endif