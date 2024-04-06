#ifndef _COMPRESSION_H_
#define _COMPRESSION_H_

#include "../constants.h"
#include "../tree/huffman_tree.h"
#include "../tree/alphabet.h"
#include "../utils/file.h"
#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void compress_files(char **input_files, char *output_file, int num_files);

#endif