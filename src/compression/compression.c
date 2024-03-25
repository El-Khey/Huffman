#include "./compression.h"

static void write_header(FILE *file, Node **alphabet, int number_of_leaves)
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
}

static void write_bit(FILE *file, uint8_t *byte, uint8_t *bit_position, uint8_t bit)
{
    *byte = (*byte << 1) | bit;
    (*bit_position)++;

    if (*bit_position == 8)
    {
        fwrite(byte, sizeof(uint8_t), 1, file);
        *byte = 0;
        *bit_position = 0;
    }
}

static void flush_bits(FILE *file, uint8_t *byte, uint8_t *bit_position)
{
    if (*bit_position > 0)
    {
        *byte <<= (8 - *bit_position);
        fwrite(byte, sizeof(uint8_t), 1, file);
    }
}

static void write_encoded_data(FILE *file, FILE *compressed_file, Node *alphabet[])
{
    int ch;
    uint8_t byte = 0;
    uint8_t bit_position = 0;
    int i = 0;

    rewind(file);

    while ((ch = fgetc(file)) != EOF)
    {
        if (ch > MAX_CHAR || ch < 0)
        {
            fprintf(stderr, "Error: character with ASCII code %d is not supported.\n", ch);
            continue;
        }

        for (i = 0; i < alphabet[ch]->depth; i++)
        {
            write_bit(compressed_file, &byte, &bit_position, alphabet[ch]->code[i]);
        }
    }

    flush_bits(compressed_file, &byte, &bit_position);
}

void compress_file(char *input_file, char *output_file)
{
    int tab[MAX_CHAR];
    Node *leaves_nodes[MAX_CHAR], *alphabet[MAX_CHAR];
    Node *huffman_tree;
    int number_of_leaves;

    FILE *file = fopen(input_file, "r");
    FILE *compressed_file = fopen(output_file, "w");

    check_file_opening(file, input_file);
    check_file_opening(compressed_file, output_file);

    count_char_frequencies(file, tab);
    initialize_huffman_nodes(leaves_nodes, tab, MAX_CHAR);

    huffman_tree = create_huffman_tree(leaves_nodes, MAX_CHAR);
    number_of_leaves = get_number_of_leaves(huffman_tree);

    create_codes(huffman_tree);
    compute_alphabet(huffman_tree, alphabet);
    print_alphabet(alphabet);

    write_header(compressed_file, alphabet, number_of_leaves);
    write_encoded_data(file, compressed_file, alphabet);

    fprintf(stdout, "\n\n========================================\n");
    fprintf(stdout, "  Compression completed successfully!\n");
    fprintf(stdout, "========================================\n\n");

    fclose(file);
    fclose(compressed_file);
}