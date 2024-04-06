#ifndef _FOLDER_H_
#define _FOLDER_H_

#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * @brief Check if a folder exists
 *
 * @param directory - The directory to check
 * @return 1 if the folder exists, 0 otherwise
 */
int exists(const char *directory);

/**
 * @brief Create a folder if it doesn't exist
 *
 * @param directory - The directory to create
 */
void create_folder(char *directory);

/**
 * @brief Fix the folder name by adding a '/' at the end if it doesn't exist
 *
 * @param directory - The directory to fix
 */
void fix_folder_name(char *directory);

#endif