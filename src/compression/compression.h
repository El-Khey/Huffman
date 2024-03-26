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

void compress_file(char *input_file, char *output_file);

#endif