#ifndef _COMPRESSION_H_
#define _COMPRESSION_H_

#include "../decompression/decompression.h"
#include "../coding/tree/huffman_tree.h"
#include "../coding/alphabet/alphabet.h"
#include "../../utils/folder/folder.h"
#include "../../utils/file/file.h"
#include "../../utils/byte/bit.h"
#include "../../../debug/debug.h"
#include "../../../constants.h"
#include "../../utils/utils.h"

#include "data.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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