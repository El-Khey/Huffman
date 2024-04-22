#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 * @brief Prompt the user to override an existing file or not
 *
 * @param file - the file
 * @param filename - the filename
 */
void prompt_override_existing_file(FILE *file, const char *filename);

/**
 * @brief Check if fscanf is successful
 *
 * @param success - the success of fscanf
 * @param filename - the filename
 */
void is_fscanf_successful(int success, const char *filename);

/**
 * @brief Get the filename from a path
 *
 * @param path - the path
 * @return the filename
 */
char *get_filename(const char *path);

/**
 * @brief Check if the file is a text file
 *
 * @param filename - the filename
 * @return 1 if the file is a text file, 0 otherwise
 */
int is_text_file(const char *filename);

#endif