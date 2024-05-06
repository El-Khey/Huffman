#include "compression.h"

static void write_header(FILE *file, Header header, int number_of_files)
{
    int i;
    char *binary_code;

    fprintf(file, "%d\n", header.number_of_leaves);
    for (i = 0; i < MAX_CHAR; i++)
    {
        if (header.alphabet[i] != NULL)
        {
            int *code = convert_binary_code_into_int_array(header.alphabet[i]->code, header.alphabet[i]->depth);
            binary_code = convert_code_into_string(code, header.alphabet[i]->depth);
            fprintf(file, "%d %d %d %s\n",
                    header.alphabet[i]->ascii,
                    header.alphabet[i]->frequency,
                    header.alphabet[i]->depth,
                    binary_code);

            free(binary_code);
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
            int *code = convert_binary_code_into_int_array(alphabet[ch]->code, alphabet[ch]->depth);
            write_bit(compressed_file, &byte, &bit_position, code[i]);
            free(code);
        }
    }

    flush_bits(compressed_file, &byte, &bit_position);
    fclose(raw_file);
}

static void write_files_data(Files list, Archive archive)
{
    int i, size;
    for (i = 0; i < list.number_of_files; i++)
    {
        size = get_encoded_file_size(list.files[i].path, archive.header.alphabet);
        list.files[i].flush_size = (size % 8) ? 8 - (size % 8) : 0;
        list.files[i].total_size = size + list.files[i].flush_size;
        debug_file_size(list.files[i].path, list.files[i].total_size, list.files[i].flush_size);

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

void compress(char **inputs, char *output_file, int number_of_inputs, Type archive_type)
{
    Node *leaves_nodes[MAX_CHAR], *huffman_tree;
    int char_frequencies[MAX_CHAR], number_of_files;
    Archive archive;
    Data data;

    // Prepare the data
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
    if (!number_of_files)
    {
        fprintf(stderr, "<Warning>: Skipping compression because no files were found.\n");
        return;
    }

    int number_of_unique_chars = get_number_of_unique_chars(char_frequencies);
    debug_char_frequencies(char_frequencies);

    if (number_of_unique_chars == 1)
    {
        int ascii = get_ascii_of_unique_char(char_frequencies);
        initialize_alphabet(archive.header.alphabet);

        archive.header.number_of_leaves = 1;
        archive.header.alphabet[ascii] = create_node(ascii, char_frequencies[ascii], 1, 0);
    }
    else
    {
        // Step 1: Create the Huffman tree
        initialize_huffman_nodes(leaves_nodes, char_frequencies);
        huffman_tree = create_huffman_tree(leaves_nodes);
        archive.header.number_of_leaves = get_number_of_leaves(huffman_tree);

        // Step 2: Create the codes for each character and compute the alphabet
        create_codes(huffman_tree);
        compute_alphabet(huffman_tree, archive.header.alphabet);
    }

    debug_alphabet(archive.header.alphabet);

    // Step 4: Write the header and the encoded data to the compressed archive
    write_header(archive.file, archive.header, number_of_files);
    fclose(archive.file);

    archive.file = fopen(output_file, "ab");
    check_file_opening(archive.file, output_file);
    write_data(data, archive);

    fclose(archive.file);

    fprintf(stdout, "\n\n========================================\n");
    fprintf(stdout, "  Compression completed successfully!\n");
    fprintf(stdout, "========================================\n\n");
}