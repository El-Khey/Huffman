#ifndef _COMPRESSION_H_
#define _COMPRESSION_H_

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

/**
 * @brief Compresses the input folders into the archive file.
 *
 * @param input_folders - array of input folders
 * @param output_file - output archive file
 * @param number_of_folders  - number of input folders
 */
void compress_folders(char **input_folders, char *output_file, int number_of_folders);

/**
 * @brief Compresses the input files into the archive file.
 *
 * @param input_files - array of input files
 * @param output_file - output archive file
 * @param number_of_files - number of input files
 */
void compress_files(char **input_files, char *output_file, int num_files);

#endif