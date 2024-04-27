#ifndef _FOLDER_H_
#define _FOLDER_H_

#include "../utils.h"
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Check if a folder exists
 *
 * @param directory - The directory to check
 * @return 1 if the folder exists, 0 otherwise
 */
int exists(const char *directory);

/**
 * @brief Get the name of a folder
 *
 * @param directory - The directory to get the name from
 * @return The name of the folder
 */
char *get_folder_name(char *directory);

/**
 * @brief Get the absolute path of a folder
 *
 * @param directory - The directory to get the absolute path from
 * @return The absolute path of the folder
 */
char *get_absolute_path(char *directory);

/**
 * @brief Get the parent directory of a folder
 *
 * @param directory - The directory to get the parent directory from
 * @return The parent directory of the folder
 */
char *get_parent_directory(char *directory);

/**
 * @brief Create intermediate folders if they don't exist
 *
 * @param directory - The directory to create
 */
void create_intermediate_folders(char *directory);

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

/**
 * @brief Get the depth of a folder tree
 *
 * @param directory - The directory to check
 * @return The depth of the folder tree
 */
int get_folder_tree_depth(char *directory);

/**
 * @brief Find the deepest level of a directory
 *
 * @param base_path - The base path of the directory
 * @param dir_path - The directory to check
 * @param level - The level of the directory
 * @return The deepest level of the directory
 */
void find_deepest_level(char *base_path, char *dir_path, int *level);

/**
 * @brief Get the number of files in a directory
 *
 * @param dir_path - The directory to check
 * @param level - The level of the directory
 * @param extension - The extension of the files
 * @return The number of files in the directory
 */
int get_number_files(char *dir_path, int level, char *extension);

/**
 * @brief Get the relative level of a folder
 *
 * @param base_dir - The base directory
 * @param sub_dir - The sub directory
 * @return The relative level of the folder
 */
int get_folder_relative_level(char *base_dir, char *sub_dir);

/**
 * @brief List the files in a directory
 *
 * @param dir_path - The directory to check
 * @param level - The level of the directory
 * @param files_list - The list of files in the directory
 * @param index_files - The index of the files
 */
void list_files_in_folder_at_level(char *dir_path, int level, char **files_list);

/**
 * @brief Check if a folder can be opened
 *
 * @param dir - The directory to check
 * @param directory_name - The name of the directory
 */
void check_folder_opening(DIR *dir, const char *directory_name);

/**
 * @brief Count the number of directories inside a folder
 *
 * @param directory - The directory to check
 * @return The number of directories inside the folder
 */
int count_number_dir_inside_folder(char *directory);

#endif