#include "compression.h"

// TODO : compress only 1 letter
static void write_header(FILE *file, Node **alphabet, int number_of_leaves, int number_of_files)
{
    int i;
    char *binary_code;

    fprintf(file, "%d\n", number_of_leaves);
    for (i = 0; i < MAX_CHAR; i++)
    {
        if (alphabet[i] != NULL)
        {
            binary_code = convert_code_into_string(alphabet[i]->code, alphabet[i]->depth);
            fprintf(file, "%d %d %d %s\n",
                    alphabet[i]->ascii,
                    alphabet[i]->frequency,
                    alphabet[i]->depth,
                    binary_code);
        }
    }
    fprintf(file, "Number of files:%d", number_of_files);
}

static int get_encoded_file_size(FILE *raw_file, Node **alphabet)
{
    int size = 0;
    int ch;

    while ((ch = fgetc(raw_file)) != EOF)
    {
        if (ch > MAX_CHAR || ch < 0)
        {
            fprintf(stderr, "Error: character with ASCII code %d is not supported.\n", ch);
            continue;
        }

        size += alphabet[ch]->depth;
    }

    rewind(raw_file);
    return size;
}

static void write_encoded_data(FILE *raw_file, char *filename, FILE *compressed_file, Node **alphabet)
{
    int ch;
    uint8_t byte = 0;
    uint8_t bit_position = 0;
    int i = 0, size = 0, flush_size = 0;
    int filename_length = strlen(filename);

    size = get_encoded_file_size(raw_file, alphabet);
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

void compress_folders(char **input_folders, char *output_file, int number_of_folders)
{
    int i = 0;
    char **files_list;
    int number_of_files = 0;
    int level = 0;
    int index_files = 0;

    printf("List of folders Passed: %d\n\n", number_of_folders);

    // TODO: loop to count the total number of files
    for (i = 0; i < number_of_folders; i++)
    {
        find_deepest_level(input_folders[i], input_folders[i], &level);
        number_of_files += get_number_files(input_folders[i], level);
    }

    printf("Number of files: %d\n", number_of_files);

    files_list = (char **)malloc(number_of_files * sizeof(char *));
    for (i = 0; i < number_of_folders; i++)
    {
        find_deepest_level(input_folders[i], input_folders[i], &level);
        list_files_in_folder_at_level(input_folders[i], level, files_list, &index_files);
    }

    for (int j = 0; j < number_of_files; j++)
    {
        printf("->File[%d]: %s\n", j, files_list[j]);
    }

    // ! compress_files(files_list, output_file, number_of_files);
    // TODO : check the files names to store in the header of the compressed file
}

void compress_files(char **input_files, char *output_file, int number_of_files)
{
    int char_frequencies[MAX_CHAR];
    Node *leaves_nodes[MAX_CHAR], *alphabet[MAX_CHAR];
    Node *huffman_tree;
    int number_of_leaves;

    FILE *compressed_archive = fopen(output_file, "r");
    FILE *raw_file = NULL;

    // Prepare the compressed archive
    prompt_override_existing_file(compressed_archive, output_file);
    compressed_archive = fopen(output_file, "wb");
    check_file_opening(compressed_archive, output_file);

    // Pre-step: Count the frequency of each character in the files
    initialize_char_frequencies(char_frequencies);
    for (int i = 0; i < number_of_files; i++)
    {
        raw_file = fopen(input_files[i], "r");
        check_file_opening(raw_file, input_files[i]);
        count_char_frequencies(raw_file, char_frequencies);
        fclose(raw_file);
    }

    display_char_frequencies(char_frequencies); // ! TODO: use a debug flag to trigger this line

    // Step 1: Create the Huffman tree
    initialize_huffman_nodes(leaves_nodes, char_frequencies);
    huffman_tree = create_huffman_tree(leaves_nodes);
    number_of_leaves = get_number_of_leaves(huffman_tree);
    printf("Number of leaves: %d\n", number_of_leaves);

    // Step 2: Create the codes for each character and compute the alphabet
    create_codes(huffman_tree);
    compute_alphabet(huffman_tree, alphabet);
    print_alphabet(alphabet); // ! TODO: use a debug flag to trigger this line

    // Step 4: Write the header and the encoded data to the compressed archive
    write_header(compressed_archive, alphabet, number_of_leaves, number_of_files);
    fclose(compressed_archive);

    compressed_archive = fopen(output_file, "ab");
    check_file_opening(compressed_archive, output_file);
    for (int i = 0; i < number_of_files; i++)
    {
        raw_file = fopen(input_files[i], "r");
        compressed_archive = fopen(output_file, "ab");
        write_encoded_data(raw_file, input_files[i], compressed_archive, alphabet);
        fclose(raw_file);
        fclose(compressed_archive);
    }

    fprintf(stdout, "\n\n========================================\n");
    fprintf(stdout, "  Compression completed successfully!\n");
    fprintf(stdout, "========================================\n\n");
}