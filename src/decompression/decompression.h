#ifndef _DECOMPRESSION_H_
#define _DECOMPRESSION_H_

#include "../constants.h"
#include "../tree/huffman_tree.h"
#include "../utils/file.h"
#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>

void decompress_file(char *input_file, char *output_file);

#endif