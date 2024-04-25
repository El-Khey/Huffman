#ifndef _EXPLORE_H_
#define _EXPLORE_H_

#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../../../huffman/utils/folder/folder.h"
#include "../../../huffman/utils/file/file.h"

typedef struct
{
    long size;
    char last_modified[20];
    char *type;
} Metadata;

typedef struct
{
    char *path;
    char *name;
    Metadata metadata;
    DIR *dir;
} Dir;

typedef struct
{
    int number_of_directories;
    Dir *list;
} Dirs;

typedef struct
{
    char *path;
    char *name;
    Metadata metadata;
    FILE *file;
} Doc;

typedef struct
{
    int number_of_files;
    Doc *list;
} Docs;

typedef struct
{
    Dirs directories;
    Docs files;

    Dir current_directory;
} Explorer;

/**
 * @brief Construct the explorer
 *
 * @param path The path to explore
 * @return Explorer
 */
Explorer construct_explorer(char *path);

/**
 * @brief Explore the path
 *
 * @param explorer The explorer
 * @param path The path to explore
 */
void explore(Explorer *explorer, char *path);

/**
 * @brief Order the files
 *
 * @param files The files
 */
void order_files(Docs *files);

/**
 * @brief Order the directories
 *
 * @param directories The directories
 */
void order_directories(Dirs *directories);

/**
 * @brief Print the explorer
 *
 * @param explorer The explorer
 */
void print_explorer(Explorer explorer);

#endif