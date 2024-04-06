#include "folder.h"

int exists(const char *directory)
{
    return access(directory, F_OK) == 0;
}

void fix_folder_name(char *directory)
{
    if (directory[strlen(directory) - 1] != '/')
    {
        strcat(directory, "/");
    }
}

void create_folder(char *directory)
{
    if (strcmp(directory, "./") == 0)
    {
        return;
    }

    fix_folder_name(directory);
    if (exists(directory))
    {
        fprintf(stderr, "<Warning>: The directory %s already exists\n", directory);
    }

    else if (mkdir(directory, 0777) == -1)
    {
        fprintf(stderr, "<Error>: Could not create the directory %s\n", directory);
        exit(EXIT_FAILURE);
    }
}
