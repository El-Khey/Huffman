#ifndef _DATA_H_
#define _DATA_H_

#include "../utils/folder.h"
#include "../utils/file.h"
#include "../constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct File
{
    char *path;
    char *name;

    int total_size;
    int flush_size;

    int *encoded_data;
    int length_encoded_data;
} File;

typedef struct Files
{
    int number_of_files;
    File *files;
} Files;

typedef struct Directory
{
    char *path;
    char *name;

    Files list;
} Directory;

typedef struct Directories
{
    int number_of_directories;
    Directory *directories;
} Directories;

typedef struct Data
{
    Directories directories;
    Files files;
    Type type;
} Data;

void compute_char_frequencies_in_files(Files files, int *char_frequencies);

void compute_char_frequencies_in_folders(Directories directories, int *char_frequencies);

int get_number_files_in_directories(Directories directories);

void prepare_data(Data *data, char **inputs, int number_of_inputs, Type archive_type);

#endif