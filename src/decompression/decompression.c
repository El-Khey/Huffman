#include "decompression.h"

static void read_header(FILE *file, Node **alphabet)
{
    int n, i, frequency, size, success, ascii;
    char binary_code[MAX_CHAR];
    int *code;

    success = fscanf(file, "%d\n", &n);
    if (!success)
    {
        fprintf(stderr, "Error: could not read the number of leaves.\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < MAX_CHAR; i++)
    {
        if (i < n)
        {
            success = fscanf(file, "%d %d %d %s\n", &ascii, &frequency, &size, binary_code);
            if (!success)
            {
                fprintf(stderr, "Error: could not read the header.\n");
                exit(EXIT_FAILURE);
            }

            code = (int *)malloc(size * sizeof(int));
            code = convert_string_into_code(binary_code, size);

            alphabet[i] = create_node(ascii, frequency, size, code);
        }
        else
        {
            alphabet[i] = NULL;
        }
    }
}

static int get_length_encoded_data(Node **alphabet)
{
    int i, length = 0;

    for (i = 0; i < MAX_CHAR; i++)
    {
        if (alphabet[i] != NULL)
        {
            length += alphabet[i]->frequency * alphabet[i]->depth;
        }
    }

    return length;
}

static int read_bit(FILE *file, uint8_t *byte, uint8_t *bit_position)
{
    int bit;

    if (*bit_position == 0)
    {
        if (fread(byte, sizeof(uint8_t), 1, file) != 1)
        {
            return -1;
        }

        *bit_position = 8;
    }

    bit = (*byte >> (*bit_position - 1)) & 1;
    (*bit_position)--;

    return bit;
}

static void read_encoded_data(FILE *input, int *encoded_data)
{
    int bit;
    uint8_t byte = 0;
    uint8_t bit_position = 0;
    int i = 0;

    while ((bit = read_bit(input, &byte, &bit_position)) != -1)
    {
        encoded_data[i] = bit;
        i++;
    }
}

static void decode(Node **alphabet, int *encoded_data, int length_encoded_data, FILE *output)
{
    int i = 0;
    int processed_length = 0;
    int code_found = 1;
    int index;

    while (1)
    {
        index = (i % MAX_CHAR);

        if (alphabet[index] == NULL)
        {
            i++;
            continue;
        }

        if (processed_length >= length_encoded_data)
        {
            break;
        }

        code_found = 1;
        code_found = are_arrays_equal(alphabet[index]->code, encoded_data, processed_length, alphabet[index]->depth);

        if (code_found)
        {
            fprintf(output, "%c", alphabet[index]->ascii);
            processed_length += alphabet[index]->depth;
        }

        i++;
    }
}

void decompress_file(char *input_file, char *output_file)
{
    Node *alphabet[MAX_CHAR];

    int length_encoded_data;
    FILE *input = fopen(input_file, "rb");
    FILE *output = fopen(output_file, "wb");
    int *encoded_data;

    check_file_opening(input, input_file);
    check_file_opening(output, output_file);

    read_header(input, alphabet);

    length_encoded_data = get_length_encoded_data(alphabet);
    encoded_data = (int *)malloc(length_encoded_data * sizeof(int));

    read_encoded_data(input, encoded_data);

    decode(alphabet, encoded_data, length_encoded_data, output);

    fprintf(stdout, "\n\n========================================\n");
    fprintf(stdout, "  Decompression completed successfully!\n");
    fprintf(stdout, "========================================\n\n");

    fclose(input);
    fclose(output);
}