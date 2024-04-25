#include "explorer.h"

Explorer construct_explorer()
{
    Explorer explorer;

    explorer.directories.number_of_directories = 0;
    explorer.files.number_of_files = 0;

    return explorer;
}

static long get_directory_size(const char *path)
{
    long size = 0;
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    dir = opendir(path);
    if (dir == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL)
    {
        char entry_path[1024];
        snprintf(entry_path, sizeof(entry_path), "%s/%s", path, entry->d_name);

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        if (stat(entry_path, &file_stat) == 0)
        {
            if (S_ISREG(file_stat.st_mode))
            {
                size += file_stat.st_size; // Add size of regular file
            }
            else if (S_ISDIR(file_stat.st_mode))
            {
                size += get_directory_size(entry_path); // Recursively get size of subdirectory
            }
        }
    }
    closedir(dir);
    return size;
}

void explore(Explorer *explorer, char *path)
{
    struct dirent *entry;
    struct stat file_stat;

    explorer->current_directory.path = path;
    explorer->current_directory.name = get_folder_name(path);
    explorer->current_directory.dir = opendir(path);

    explorer->directories.number_of_directories = count_number_dir_inside_folder(path);
    explorer->files.number_of_files = get_number_files(path, 0);

    explorer->directories.list = malloc(explorer->directories.number_of_directories * sizeof(Dir));
    explorer->files.list = malloc(explorer->files.number_of_files * sizeof(Doc));

    int number_of_directories = 0;
    int number_of_files = 0;

    while ((entry = readdir(explorer->current_directory.dir)) != NULL)
    {
        char *entry_path = malloc(strlen(path) + strlen(entry->d_name) + 2);
        sprintf(entry_path, "%s/%s", path, entry->d_name);

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        if (stat(entry_path, &file_stat) == 0)
        {
            if (S_ISDIR(file_stat.st_mode))
            {
                Dir directory;
                time_t mod_time = file_stat.st_mtime;
                struct tm *tm_info = localtime(&mod_time);

                directory.path = entry_path;
                directory.name = entry->d_name;

                Metadata metadata;
                metadata.size = get_directory_size(entry_path);

                strftime(metadata.last_modified, sizeof(metadata.last_modified), "%Y-%m-%d %H:%M:%S", tm_info);
                metadata.type = "Directory";
                directory.metadata = metadata;

                explorer->directories.list[number_of_directories] = directory;
                number_of_directories++;
            }
            else if (S_ISREG(file_stat.st_mode) && is_text_file(entry_path))
            {
                Doc file;
                time_t mod_time = file_stat.st_mtime;
                struct tm *tm_info = localtime(&mod_time);

                file.path = entry_path;
                file.name = entry->d_name;

                Metadata metadata;
                metadata.size = file_stat.st_size;

                strftime(metadata.last_modified, sizeof(metadata.last_modified), "%Y-%m-%d %H:%M:%S", tm_info);
                metadata.type = "File";
                file.metadata = metadata;

                explorer->files.list[number_of_files] = file;
                number_of_files++;
            }
        }
    }
}

void print_explorer(Explorer explorer)
{
    printf("Current directory: %s\n", explorer.current_directory.path);
    printf("Directories:\n");
    printf("| %-20s | %-20s | %-10s | %-20s | %-10s |\n", "Name", "Path", "Size", "Last Modified", "Type");
    printf("|----------------------|----------------------|-----------|----------------------|-----------|\n");
    for (int i = 0; i < explorer.directories.number_of_directories; i++)
    {
        Dir directory = explorer.directories.list[i];
        printf("| %-20s | %-20s | %-10ld | %-20s | %-10s |\n", directory.name, directory.path, directory.metadata.size, directory.metadata.last_modified, directory.metadata.type);
    }

    printf("Files:\n");
    printf("| %-20s | %-20s | %-10s | %-20s | %-10s |\n", "Name", "Path", "Size", "Last Modified", "Type");
    printf("|----------------------|----------------------|-----------|----------------------|-----------|\n");
    for (int i = 0; i < explorer.files.number_of_files; i++)
    {
        Doc file = explorer.files.list[i];
        printf("| %-20s | %-20s | %-10ld | %-20s | %-10s |\n", file.name, file.path, file.metadata.size, file.metadata.last_modified, file.metadata.type);
    }
}

static int compare_file(const void *a, const void *b)
{
    Doc *file_a = (Doc *)a;
    Doc *file_b = (Doc *)b;

    return strcmp(file_a->name, file_b->name);
}

static int compare_dir(const void *a, const void *b)
{
    Dir *dir_a = (Dir *)a;
    Dir *dir_b = (Dir *)b;

    return strcmp(dir_a->name, dir_b->name);
}

void order_directories(Dirs *directories)
{
    qsort(directories->list, directories->number_of_directories, sizeof(Dir), compare_dir);
}

void order_files(Docs *files)
{
    qsort(files->list, files->number_of_files, sizeof(Doc), compare_file);
}