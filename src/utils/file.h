#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief This function use fread to read and display partial content of a file
 *
 * @param filename
 */
void read_partial_content(const char *filename);

/**
 * @brief This function use fgetc to read and display full content of a file
 *
 * @param filename
 */
void read_full_content(const char *filename);

/**
 * @brief Check if the file is opened
 *
 * @param file - the file
 * @param filename - the filename
 */
void check_file_opening(FILE *file, const char *filename);

/**
 * @brief Check if the file exists
 *
 * @param file - the file
 * @param filename - the filename
 */
void check_file_existence(FILE *file);

#endif