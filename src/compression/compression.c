#include "compression.h"

// TODO : compress only 1 letter
static void write_header(FILE *file, Header header, int number_of_files)
{
    int i;
    char *binary_code;

    fprintf(file, "%d\n", header.number_of_leaves);
    for (i = 0; i < MAX_CHAR; i++)
    {
        if (header.alphabet[i] != NULL)
        {
            binary_code = convert_code_into_string(header.alphabet[i]->code, header.alphabet[i]->depth);
            fprintf(file, "%d %d %d %s\n",
                    header.alphabet[i]->ascii,
                    header.alphabet[i]->frequency,
                    header.alphabet[i]->depth,
                    binary_code);
        }
    }
    fprintf(file, "n:%d", number_of_files);
}

static int get_encoded_file_size(char *filename, Node **alphabet)
{
    int size = 0;
    int ch;
    FILE *raw_file = fopen(filename, "r");

    while ((ch = fgetc(raw_file)) != EOF)
    {
        if (ch > MAX_CHAR || ch < 0)
        {
            fprintf(stderr, "Error: character with ASCII code %d is not supported.\n", ch);
            continue;
        }

        size += alphabet[ch]->depth;
    }

    fclose(raw_file);
    return size;
}

static void write_encoded_data(File file, FILE *compressed_file, Node **alphabet)
{
    int ch;
    uint8_t byte = 0;
    uint8_t bit_position = 0;
    int i = 0;

    debug_file_size(file.name, file.total_size, file.flush_size); // ! TODO: use a debug flag to trigger this line
    fprintf(compressed_file, "\nlength:%d\n", (int)strlen(file.name));
    fprintf(compressed_file, "file:%s encoded_size:%d flush_size:%d\n", file.name, file.total_size, file.flush_size);

    FILE *raw_file = fopen(file.path, "r");
    while ((ch = fgetc(raw_file)) != EOF)
    {
        if (ch > MAX_CHAR || ch < 0)
        {
            fprintf(stderr, "<Error>: character with ASCII code %d is not supported.\n", ch);
            continue;
        }

        for (i = 0; i < alphabet[ch]->depth; i++)
        {
            write_bit(compressed_file, &byte, &bit_position, alphabet[ch]->code[i]);
        }
    }

    flush_bits(compressed_file, &byte, &bit_position);
}

static void write_files_data(Files list, Archive archive)
{
    int i, size;
    for (i = 0; i < list.number_of_files; i++)
    {
        size = get_encoded_file_size(list.files[i].path, archive.header.alphabet);
        list.files[i].flush_size = (size % 8) ? 8 - (size % 8) : 0;
        list.files[i].total_size = size + list.files[i].flush_size;

        write_encoded_data(list.files[i], archive.file, archive.header.alphabet);
    }
}

static void write_folders_data(Directories directories, Archive archive)
{
    int i;
    for (i = 0; i < directories.number_of_directories; i++)
    {
        write_files_data(directories.directories[i].list, archive);
    }
}

static void write_data(Data data, Archive archive)
{
    write_folders_data(data.directories, archive);
    write_files_data(data.files, archive);
}

static void compute_char_frequencies_in_files(Files files, int *char_frequencies)
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

static void compute_char_frequencies_in_folders(Directories directories, int *char_frequencies)
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

static int get_number_files_in_directories(Directories directories)
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

    printf("List of folders Passed: %d\n\n", number_of_folders);
    for (i = 0; i < number_of_folders; i++)
    {
        data->directories.directories[i].path = (char *)malloc(strlen(input_folders[i]) + 1);
        strcpy(data->directories.directories[i].path, input_folders[i]);

        data->directories.directories[i].name = (char *)malloc(strlen(input_folders[i]) + 1);
        strcpy(data->directories.directories[i].name, get_folder_name(input_folders[i]));

        find_deepest_level(input_folders[i], input_folders[i], &level);
        data->directories.directories[i].list.number_of_files = get_number_files(input_folders[i], level);

        files_path = (char **)malloc(data->directories.directories[i].list.number_of_files * sizeof(char *));
        list_files_in_folder_at_level(input_folders[i], level, files_path);

        data->directories.directories[i].list.files = (File *)malloc(data->directories.directories[i].list.number_of_files * sizeof(File));
        for (int j = 0; j < data->directories.directories[i].list.number_of_files; j++)
        {
            data->directories.directories[i].list.files[j].path = (char *)malloc(strlen(files_path[j]) + 1 * sizeof(char));
            strcpy(data->directories.directories[i].list.files[j].path, files_path[j]);

            data->directories.directories[i].list.files[j].name = files_path[j];
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

static void prepare_data(Data *data, char **inputs, int number_of_inputs, Type archive_type)
{
    int number_of_files = 0;
    int number_of_folders = 0;
    char **folders = NULL;
    char **files = NULL;

    for (int i = 0; i < number_of_inputs; i++)
    {
        if (is_text_file(inputs[i]))
        {
            files = (char **)realloc(files, number_of_files * sizeof(char *));
            files[number_of_files] = inputs[i];
            number_of_files++;
        }
        else
        {
            folders = (char **)realloc(folders, number_of_folders * sizeof(char *));
            folders[number_of_folders] = inputs[i];
            number_of_folders++;
        }
    }

    prepare_folders_data(data, folders, number_of_folders);
    prepare_files_data(data, files, number_of_files);
    data->type = (BOTH_TYPE == archive_type) ? BOTH_TYPE : archive_type;
}

void compress(char **inputs, char *output_file, int number_of_inputs, Type archive_type)
{
    Node *leaves_nodes[MAX_CHAR], *huffman_tree;
    int char_frequencies[MAX_CHAR], number_of_files;
    Archive archive;
    Data data;

    prepare_data(&data, inputs, number_of_inputs, archive_type);

    // Prepare the compressed archive
    prompt_override_existing_file(fopen(output_file, "r"), output_file);
    archive.file = fopen(output_file, "wb");
    check_file_opening(archive.file, output_file);

    // Pre-step: Count the frequency of each character in the files
    initialize_char_frequencies(char_frequencies);
    compute_char_frequencies_in_folders(data.directories, char_frequencies);
    compute_char_frequencies_in_files(data.files, char_frequencies);

    number_of_files = get_number_files_in_directories(data.directories) + data.files.number_of_files;
    display_char_frequencies(char_frequencies); // ! TODO: use a debug flag to trigger this line

    // Step 1: Create the Huffman tree
    initialize_huffman_nodes(leaves_nodes, char_frequencies);
    huffman_tree = create_huffman_tree(leaves_nodes);
    archive.header.number_of_leaves = get_number_of_leaves(huffman_tree);

    // Step 2: Create the codes for each character and compute the alphabet
    create_codes(huffman_tree);
    compute_alphabet(huffman_tree, archive.header.alphabet);
    print_alphabet(archive.header.alphabet); // ! TODO: use a debug flag to trigger this line

    // Step 4: Write the header and the encoded data to the compressed archive
    write_header(archive.file, archive.header, number_of_files);
    fclose(archive.file);

    archive.file = fopen(output_file, "ab");
    check_file_opening(archive.file, output_file);
    write_data(data, archive);

    fprintf(stdout, "\n\n========================================\n");
    fprintf(stdout, "  Compression completed successfully!\n");
    fprintf(stdout, "========================================\n\n");
}