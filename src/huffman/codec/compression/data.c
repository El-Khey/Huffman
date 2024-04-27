#include "data.h"

void compute_char_frequencies_in_files(Files files, int *char_frequencies)
{
    int i;
    for (i = 0; i < files.number_of_files; i++)
    {
        FILE *file = fopen(files.files[i].path, "r");
        check_file_opening(file, files.files[i].path);
        count_char_frequencies(file, char_frequencies);
        fclose(file);
    }
}

void compute_char_frequencies_in_folders(Directories directories, int *char_frequencies)
{
    int i, j;
    for (i = 0; i < directories.number_of_directories; i++)
    {
        for (j = 0; j < directories.directories[i].list.number_of_files; j++)
        {
            compute_char_frequencies_in_files(directories.directories[i].list, char_frequencies);
        }
    }
}

int get_number_files_in_directories(Directories directories)
{
    int i, number_of_files = 0;
    for (i = 0; i < directories.number_of_directories; i++)
    {
        number_of_files += directories.directories[i].list.number_of_files;
    }
    return number_of_files;
}

static void prepare_folders_data(Data *data, char **input_folders, int number_of_folders)
{
    int i = 0;
    int level = 0;
    char **files_path;

    data->type = FOLDER_TYPE;
    data->directories.number_of_directories = number_of_folders;
    data->directories.directories = (Directory *)malloc(number_of_folders * sizeof(Directory));

    for (i = 0; i < number_of_folders; i++)
    {
        data->directories.directories[i].path = (char *)malloc(strlen(input_folders[i]) + 1);
        strcpy(data->directories.directories[i].path, input_folders[i]);

        data->directories.directories[i].name = (char *)malloc(strlen(input_folders[i]) + 1);
        strcpy(data->directories.directories[i].name, get_folder_name(input_folders[i]));

        find_deepest_level(input_folders[i], input_folders[i], &level);
        data->directories.directories[i].list.number_of_files = get_number_files(input_folders[i], level, ".txt");

        files_path = (char **)malloc(data->directories.directories[i].list.number_of_files * sizeof(char *));
        list_files_in_folder_at_level(input_folders[i], level, files_path);

        data->directories.directories[i].list.files = (File *)malloc(data->directories.directories[i].list.number_of_files * sizeof(File));
        for (int j = 0; j < data->directories.directories[i].list.number_of_files; j++)
        {
            data->directories.directories[i].list.files[j].path = (char *)malloc(strlen(files_path[j]) + 1 * sizeof(char));
            data->directories.directories[i].list.files[j].name = (char *)malloc(strlen(files_path[j]) + 1 * sizeof(char));

            strcpy(data->directories.directories[i].list.files[j].path, files_path[j]);
            strcpy(data->directories.directories[i].list.files[j].name, files_path[j]);

            data->directories.directories[i].list.files[j].name += strlen(input_folders[i]);
            str_cat_prefix(data->directories.directories[i].list.files[j].name, get_folder_name(input_folders[i]));
        }
    }
}

static void prepare_files_data(Data *data, char **input_files, int number_of_files)
{
    data->type = FILE_TYPE;
    data->files.number_of_files = number_of_files;
    data->files.files = (File *)malloc(number_of_files * sizeof(File));

    for (int i = 0; i < number_of_files; i++)
    {
        data->files.files[i].path = (char *)malloc(strlen(input_files[i]) + 1 * sizeof(char));

        strcpy(data->files.files[i].path, input_files[i]);
        data->files.files[i].name = get_filename(input_files[i]);
    }
}

void prepare_data(Data *data, char **inputs, int number_of_inputs, Type archive_type)
{
    int number_of_files = 0;
    int number_of_folders = 0;
    char **folders = (char **)malloc(number_of_inputs * sizeof(char *));
    char **files = (char **)malloc(number_of_inputs * sizeof(char *));

    for (int i = 0; i < number_of_inputs; i++)
    {
        if (is_text_file(inputs[i]))
        {
            files[number_of_files] = inputs[i];
            number_of_files++;
        }
        else
        {
            folders[number_of_folders] = inputs[i];
            number_of_folders++;
        }
    }

    prepare_folders_data(data, folders, number_of_folders);
    prepare_files_data(data, files, number_of_files);
    data->type = (BOTH_TYPE == archive_type) ? BOTH_TYPE : archive_type;
}
