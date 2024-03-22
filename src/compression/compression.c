#include "./compression.h"

static void write_header(FILE *file, Node *alphabet[], int number_of_leaves)
{
    int i;
    char *binary_code;
    fprintf(file, "%d\n", number_of_leaves);

    for (i = 0; i < MAX_CHAR; i++)
    {
        if (alphabet[i] != NULL)
        {
            binary_code = convert_into_bits(alphabet[i]->code, alphabet[i]->depth);
            fprintf(file, "%c %d %d %s\n",
                    alphabet[i]->character,
                    alphabet[i]->frequency,
                    alphabet[i]->depth,
                    binary_code);
        }
    }
}

static void write_encoded_data(FILE *file, FILE *compressed_file, Node *alphabet[])
{
    int ch;
    char *binary_code;

    rewind(file);

    while ((ch = fgetc(file)) != EOF)
    {
        if (ch > MAX_CHAR || ch < 0)
        {
            fprintf(stderr, "Error: character with ASCII code %d is not supported.\n", ch);
            continue;
        }

        binary_code = convert_into_bits(alphabet[ch]->code, alphabet[ch]->depth);
        fprintf(compressed_file, "%s", binary_code);
    }
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
    display_char_frequencies(tab);

    initialize_huffman_nodes(leaves_nodes, tab, MAX_CHAR);
    printf("Huffman nodes initialized.\n");

    huffman_tree = create_huffman_tree(leaves_nodes, MAX_CHAR);
    number_of_leaves = get_number_of_leaves(huffman_tree);
    printf("Huffman tree created.\n");

    create_codes(huffman_tree);

    print_tree(huffman_tree);
    printf("\n\n");

    print_codes(huffman_tree);

    compute_alphabet(huffman_tree, alphabet);
    printf("Alphabet computed.\n");

    write_header(compressed_file, alphabet, number_of_leaves);
    printf("%d\n", number_of_leaves);
    printf("Header written.\n");

    write_encoded_data(file, compressed_file, alphabet);
    printf("Data encoded.\n");

    fclose(file);
    fclose(compressed_file);
}