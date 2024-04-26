#include "folder.h"

int exists(const char *directory)
{
    return access(directory, F_OK) == 0;
}

char *get_folder_name(char *directory)
{
    char *parts[1024]; // TODO: decide a length for the parts array based on linux/windows limits
    int size = split_string(directory, parts, "/");

    return parts[size - 1];
}

char *get_absolute_path(char *directory)
{
    char *absolute_path = realpath(directory, NULL);
    if (absolute_path == NULL)
    {
        perror("realpath");
        return directory;
    }

    return absolute_path;
}

char *get_parent_directory(char *directory)
{
    char *parts[1024]; // TODO: decide a length for the parts array based on linux/windows limits
    int size = split_string(directory, parts, "/");

    char *parent_directory = (char *)malloc(1024 * sizeof(char));
    strcpy(parent_directory, "/");
    for (int i = 0; i < size - 1; i++)
    {
        strcat(parent_directory, parts[i]);
        strcat(parent_directory, "/");
    }

    fix_folder_name(parent_directory);
    return parent_directory;
}

void fix_folder_name(char *directory)
{
    if (directory[strlen(directory) - 1] != '/')
    {
        strcat(directory, "/");
    }
}

void create_intermediate_folders(char *directory)
{
    char *parts[1024]; // TODO: decide a length for the parts array based on linux/windows limits
    int size = split_string(directory, parts, "/");

    char *current_path = (char *)malloc(1024 * sizeof(char));
    strcpy(current_path, parts[0]);
    for (int i = 1; i < size; i++)
    {
        // Check if the current part is a file extension
        if (strchr(parts[i], '.') != NULL)
        {
            break;
        }

        strcat(current_path, "/");
        strcat(current_path, parts[i]);
        create_folder(current_path);
    }

    free(current_path);
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

int get_folder_tree_depth(char *directory)
{
    int depth = 0;
    if (directory == NULL || *directory == '\0')
    {
        return depth;
    }

    char *parts[1024]; // TODO: decide a length for the parts array based on linux/windows limits
    int size = split_string(directory, parts, "/");
    for (int i = 0; i < size; i++)
    {
        // ignore the . and .. directories
        if (strcmp(parts[i], ".") == 0 || strcmp(parts[i], "..") == 0)
        {
            continue;
        }

        depth++;
    }

    return depth;
}

// TODO: create a helper function to reduce the number of parameters (base_path, level)
void find_deepest_level(char *base_path, char *dir_path, int *level)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(dir_path);
    check_folder_opening(dir, dir_path);

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            char file_path[1024];
            snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);

            DIR *sub_dir = opendir(file_path);
            if (sub_dir != NULL)
            {
                *level += 1; // TODO: move this inside the function call
                find_deepest_level(base_path, file_path, level);
                closedir(sub_dir);
            }
        }
    }

    closedir(dir);
}

int get_folder_relative_level(char *base_dir, char *sub_dir)
{
    char *base_parts[1024], *target_parts[1024];
    int base_size = split_string(base_dir, base_parts, "/");
    int target_size = split_string(sub_dir, target_parts, "/");

    return target_size - base_size;
}

static int get_number_files_helper(char *base_path, char *dir_path, int level)
{
    DIR *dir;
    struct dirent *entry;
    int num_files = 0;

    // Open directory
    dir = opendir(dir_path);
    if (dir == NULL)
    {
        fprintf(stderr, "Error opening directory %s\n", dir_path);
        return -1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            char file_path[1024];
            snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);

            DIR *sub_dir = opendir(file_path);
            if (sub_dir != NULL)
            {
                int cmp_lvl = get_folder_relative_level(base_path, file_path);
                if (cmp_lvl <= level)
                {
                    num_files += get_number_files_helper(base_path, file_path, level);
                }

                closedir(sub_dir);
            }
            else
            {
                if (strstr(entry->d_name, ".txt") != NULL)
                {
                    num_files++;
                }
            }
        }
    }

    closedir(dir);
    return num_files;
}

int get_number_files(char *dir_path, int level)
{
    return get_number_files_helper(dir_path, dir_path, level);
}

void list_files_in_folder_at_level_helper(char *base_path, char *dir_path, int level, char **files_list, int *num_files)
{
    DIR *dir;
    struct dirent *entry;

    // Open directory
    dir = opendir(dir_path);
    if (dir == NULL)
    {
        fprintf(stderr, "Error opening directory %s\n", dir_path);
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            char file_path[1024];
            snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);

            DIR *sub_dir = opendir(file_path);
            if (sub_dir != NULL)
            {
                int cmp_lvl = get_folder_relative_level(base_path, file_path);
                if (cmp_lvl <= level)
                {
                    list_files_in_folder_at_level_helper(base_path, file_path, level, files_list, num_files);
                }

                closedir(sub_dir);
            }
            else
            {
                if (strstr(entry->d_name, ".txt") != NULL)
                {
                    files_list[*num_files] = (char *)malloc(strlen(file_path) + 1 * sizeof(char));
                    strcpy(files_list[*num_files], file_path);
                    (*num_files)++;
                }
            }
        }
    }

    closedir(dir);
}

void list_files_in_folder_at_level(char *dir_path, int level, char **files_list)
{
    int index_files = 0;
    list_files_in_folder_at_level_helper(dir_path, dir_path, level, files_list, &index_files);
}

void check_folder_opening(DIR *dir, const char *directory_name)
{
    if (dir == NULL)
    {
        fprintf(stderr, "----------------------------------------------\n");
        fprintf(stderr, "Error: Could not open folder %s\n", directory_name);
        fprintf(stderr, "----------------------------------------------\n");
        exit(EXIT_FAILURE);
    }
}

int count_number_dir_inside_folder(char *directory)
{
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    int number_of_directories = 0;

    dir = opendir(directory);
    check_folder_opening(dir, directory);

    while ((entry = readdir(dir)) != NULL)
    {
        char *entry_path = malloc(strlen(directory) + strlen(entry->d_name) + 2);
        sprintf(entry_path, "%s/%s", directory, entry->d_name);

        if (stat(entry_path, &file_stat) == 0)
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && S_ISDIR(file_stat.st_mode))
            {
                number_of_directories++;
            }
        }
    }

    closedir(dir);
    return number_of_directories;
}