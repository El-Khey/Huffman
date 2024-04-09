#include "compression.h"

// TODO : compress only 1 letter
static void write_header(FILE *file, Header header, int number_of_files, Type archive_type)
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
    fprintf(file, "n:%d t:%d", number_of_files, archive_type);
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

static void write_encoded_data(FILE *raw_file, char *filename, FILE *compressed_file, Node **alphabet)
{
    int ch;
    uint8_t byte = 0;
    uint8_t bit_position = 0;
    int i = 0, size = 0, flush_size = 0;
    int filename_length = strlen(filename);

    size = get_encoded_file_size(filename, alphabet);
    flush_size = (size % 8) ? 8 - (size % 8) : 0;
    size += flush_size;

    debug_file_size(filename, size, flush_size); // ! TODO: use a debug flag to trigger this line
    fprintf(compressed_file, "\nlength:%d\n", filename_length);
    fprintf(compressed_file, "file:%s encoded_size:%d flush_size:%d\n", filename, size, flush_size);

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

static void write_files_data(Files files, FILE *compressed_file, Node **alphabet)
{
    int i;
    FILE *raw_file = NULL;

    for (i = 0; i < files.number_of_files; i++)
    {
        raw_file = fopen(files.files[i].path, "r");
        write_encoded_data(raw_file, files.files[i].path, compressed_file, alphabet);
        fclose(raw_file);
    }
}

static void write_folders_data(Directories directories, FILE *compressed_file, Node **alphabet)
{
    int i;
    for (i = 0; i < directories.number_of_directories; i++)
    {
        write_files_data(directories.directories[i].list, compressed_file, alphabet);
    }
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

static Data prepare_folders_data(char **input_folders, int number_of_folders)
{
    int i = 0;
    int level = 0;
    char **files_path;

    Data data;
    data.type = FOLDER_TYPE;
    data.directories.number_of_directories = number_of_folders;
    data.directories.directories = (Directory *)malloc(number_of_folders * sizeof(Directory));

    printf("List of folders Passed: %d\n\n", number_of_folders);
    for (i = 0; i < number_of_folders; i++)
    {
        data.directories.directories[i].path = (char *)malloc(strlen(input_folders[i]) + 1);
        strcpy(data.directories.directories[i].path, input_folders[i]);

        data.directories.directories[i].name = (char *)malloc(strlen(input_folders[i]) + 1);
        strcpy(data.directories.directories[i].name, get_folder_name(input_folders[i]));

        find_deepest_level(input_folders[i], input_folders[i], &level);
        data.directories.directories[i].list.number_of_files = get_number_files(input_folders[i], level);

        files_path = (char **)malloc(data.directories.directories[i].list.number_of_files * sizeof(char *));
        list_files_in_folder_at_level(input_folders[i], level, files_path);

        data.directories.directories[i].list.files = (File *)malloc(data.directories.directories[i].list.number_of_files * sizeof(File));
        for (int j = 0; j < data.directories.directories[i].list.number_of_files; j++)
        {
            data.directories.directories[i].list.files[j].path = (char *)malloc(strlen(files_path[j]) + 1 * sizeof(char));
            strcpy(data.directories.directories[i].list.files[j].path, files_path[j]);

            data.directories.directories[i].list.files[j].name = files_path[j];
            data.directories.directories[i].list.files[j].name += strlen(input_folders[i]);
            str_cat_prefix(data.directories.directories[i].list.files[j].name, get_folder_name(input_folders[i]));
        }
    }

    return data;
}

static Data prepare_files_data(char **input_files, int number_of_files)
{
    Data data;
    data.type = FILE_TYPE;
    data.files.number_of_files = number_of_files;
    data.files.files = (File *)malloc(number_of_files * sizeof(File));

    for (int i = 0; i < number_of_files; i++)
    {
        data.files.files[i].path = (char *)malloc(strlen(input_files[i]) + 1 * sizeof(char));
        strcpy(data.files.files[i].path, input_files[i]);

        data.files.files[i].name = get_filename(input_files[i]);
    }

    return data;
}

void compress(char **inputs, char *output_file, int number_of_inputs, Type archive_type)
{
    Node *leaves_nodes[MAX_CHAR], *huffman_tree;
    int char_frequencies[MAX_CHAR], number_of_files;
    Archive archive;

    Data data = (archive_type == FOLDER_TYPE) ? prepare_folders_data(inputs, number_of_inputs)
                                              : prepare_files_data(inputs, number_of_inputs);

    // Prepare the compressed archive
    prompt_override_existing_file(fopen(output_file, "r"), output_file);
    archive.file = fopen(output_file, "wb");
    check_file_opening(archive.file, output_file);

    // Pre-step: Count the frequency of each character in the files
    initialize_char_frequencies(char_frequencies);
    if (data.type == FOLDER_TYPE)
    {
        compute_char_frequencies_in_folders(data.directories, char_frequencies);
        number_of_files = get_number_files_in_directories(data.directories);
    }
    else
    {
        compute_char_frequencies_in_files(data.files, char_frequencies);
        number_of_files = data.files.number_of_files;
    }

    display_char_frequencies(char_frequencies); // ! TODO: use a debug flag to trigger this line

    // Step 1: Create the Huffman tree
    initialize_huffman_nodes(leaves_nodes, char_frequencies);
    huffman_tree = create_huffman_tree(leaves_nodes);
    archive.header.number_of_leaves = get_number_of_leaves(huffman_tree);
    printf("Number of leaves: %d\n", archive.header.number_of_leaves);

    // Step 2: Create the codes for each character and compute the alphabet
    create_codes(huffman_tree);
    compute_alphabet(huffman_tree, archive.header.alphabet);
    print_alphabet(archive.header.alphabet); // ! TODO: use a debug flag to trigger this line

    // Step 4: Write the header and the encoded data to the compressed archive
    write_header(archive.file, archive.header, number_of_files, data.type);
    fclose(archive.file);

    archive.file = fopen(output_file, "ab");
    check_file_opening(archive.file, output_file);
    if (data.type == FOLDER_TYPE)
    {
        write_folders_data(data.directories, archive.file, archive.header.alphabet);
    }
    else
    {
        write_files_data(data.files, archive.file, archive.header.alphabet);
    }

    fprintf(stdout, "\n\n========================================\n");
    fprintf(stdout, "  Compression completed successfully!\n");
    fprintf(stdout, "========================================\n\n");
}
