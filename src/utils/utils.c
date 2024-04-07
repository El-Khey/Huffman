#include "utils.h"

char *convert_code_into_string(int *code, int size)
{
    int i;
    char *str = (char *)malloc((size + 1) * sizeof(char));

    for (i = 0; i < size; i++)
    {
        str[i] = code[i] + '0';
    }

    str[size] = '\0';

    return str;
}

int *convert_string_into_code(char *str, int size)
{
    int i;
    int *code = (int *)malloc(size * sizeof(int));

    for (i = 0; i < size; i++)
    {
        code[i] = str[i] - '0';
    }

    return code;
}

int are_arrays_equal(int *arr1, int *arr2, int processed_length, int size)
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

void initialize_char_frequencies(int *char_frequencies)
{
    int i;
    for (i = 0; i < MAX_CHAR; i++)
    {
        char_frequencies[i] = 0;
    }
}

void count_char_frequencies(FILE *file, int *char_frequencies)
{
    int ch;

    while ((ch = fgetc(file)) != EOF)
    {
        if (ch > MAX_CHAR || ch < 0)
        {
            fprintf(stderr, "Error: character with ASCII code %d is not supported.\n", ch);
            continue;
        }

        char_frequencies[ch]++;
    }
}

void display_char_frequencies(int *char_frequencies)
{
    int i;

    printf("\n-----------------------------------\n");
    printf("\nOccurrences of each character:\n");
    for (i = 0; i < MAX_CHAR; i++)
    {
        if (char_frequencies[i] > 0)
        {
            printf("'%c' (ASCII: %d) : %d\n", i, i, char_frequencies[i]);
        }
    }

    printf("\n-----------------------------------\n");

    printf("\n");

    printf("The number of supported characters is: %d\n", i);
    printf("\n-----------------------------------\n");

    printf("\n\n");
}

void print_byte(uint8_t byte)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        printf("%d", (byte & 0x80) ? 1 : 0);
        byte <<= 1;
    }
}

int split_string(char *str, char **parts, const char *delimiter)
{
    char *token;
    int num_parts = 0;
    char *str_copy = (char *)malloc(strlen(str) + 1);
    strcpy(str_copy, str);

    if (str_copy == NULL)
    {
        fprintf(stderr, "<Error>: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize strtok with the string and delimiter
    token = strtok(str_copy, delimiter);

    // Loop through the tokens until no more tokens are found
    while (token != NULL)
    {
        parts[num_parts++] = token;      // Store the token in parts array
        token = strtok(NULL, delimiter); // Get the next token
    }

    free(str_copy);
    return num_parts; // Return the number of parts
}