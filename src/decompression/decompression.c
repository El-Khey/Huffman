#include "decompression.h"

static void read_header(FILE *file, Node **alphabet)
{
    int n, i, frequency, size, success, ascii;
    char binary_code[MAX_CHAR];
    int code;

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

            code = convert_into_int(binary_code, size);
            alphabet[i] = create_node(ascii, frequency, size, code);
        }
        else
        {
            alphabet[i] = NULL;
        }
    }
}

static void read_content(FILE *file, int *encoded_data)
{
    int ch, i = 0;

    while ((ch = fgetc(file)) != EOF)
    {
        encoded_data[i] = ch - '0';
        i++;
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

static int get_number_of_leaves_bis(Node **alphabet)
{
    int i, number_of_leaves = 0;

    for (i = 0; i < MAX_CHAR; i++)
    {
        if (alphabet[i] != NULL)
        {
            number_of_leaves++;
        }
    }

    return number_of_leaves;
}

static void print_alphabet(Node **alphabet)
{
    int i;

    for (i = 0; i < MAX_CHAR; i++)
    {
        if (alphabet[i] != NULL)
        {
            printf("ascii: %c, frequency: %d, size: %d, code: %d\n", alphabet[i]->ascii, alphabet[i]->frequency, alphabet[i]->depth, alphabet[i]->code);
        }
    }
}

static int are_arrays_equal(int *arr1, int *arr2, int processed_length, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (arr1[i] != arr2[i + processed_length])
        {
            return 0;
        }
    }

    return 1;
}

static void decode(Node **alphabet, int *encoded_data, int length_encoded_data, int number_of_leaves, FILE *output)
{
    int i = 0;
    int *decoded_code;
    int processed_length = 0;
    int code_found = 1;
    int index;

    print_alphabet(alphabet);

    printf("length_encoded_data: %d\n", length_encoded_data);
    printf("number_of_leaves: %d\n", number_of_leaves);

    while (1)
    {
        index = (i % MAX_CHAR);
        printf("index: %d\n", index);

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
        decoded_code = convert_interger_code_into_bits(alphabet[index]->code, alphabet[index]->depth);

        printf("processed_length: %d\n", processed_length);
        printf("depth: %d\n", alphabet[index]->depth);

        code_found = are_arrays_equal(decoded_code, encoded_data, processed_length, alphabet[index]->depth);
        printf("code_found: %d\n", code_found);

        if (code_found)
        {
            printf("-->: %c\n", alphabet[index]->ascii);
            fprintf(output, "%c", alphabet[index]->ascii);
            printf("ascii: %c\n", alphabet[index]->ascii);
            processed_length += alphabet[index]->depth;
            printf("-->: %d\n", processed_length);
        }

        i++;
    }
}

void decompress_file(char *input_file, char *output_file)
{
    int number_of_leaves, length_encoded_data;
    Node *alphabet[MAX_CHAR];
    int *encoded_data;

    FILE *input = fopen(input_file, "rb");
    FILE *output = fopen(output_file, "wb");

    check_file_opening(input, input_file);
    check_file_opening(output, output_file);

    read_header(input, alphabet);
    length_encoded_data = get_length_encoded_data(alphabet);

    encoded_data = (int *)malloc(length_encoded_data * sizeof(int));
    read_content(input, encoded_data);

    number_of_leaves = get_number_of_leaves_bis(alphabet);
    decode(alphabet, encoded_data, length_encoded_data, number_of_leaves, output);

    fclose(input);
    fclose(output);
}