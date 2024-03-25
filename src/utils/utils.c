#include "./utils.h"

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

void count_char_frequencies(FILE *file, int tab[MAX_CHAR])
{
    int ch, i;

    /** Initialize the array with zeros */
    for (i = 0; i < MAX_CHAR; i++)
    {
        tab[i] = 0;
    }

    /** Count occurrences of each character */
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch > MAX_CHAR || ch < 0)
        {
            fprintf(stderr, "Error: character with ASCII code %d is not supported.\n", ch);
            continue;
        }

        tab[ch]++;
    }
}

void display_char_frequencies(int tab[MAX_CHAR])
{
    int i;

    printf("\n-----------------------------------\n");
    printf("\nOccurrences of each character:\n");
    for (i = 0; i < MAX_CHAR; i++)
    {
        if (tab[i] > 0)
        {
            printf("'%c' (ASCII: %d) : %d\n", i, i, tab[i]);
        }
    }

    printf("\n-----------------------------------\n");

    printf("\n");

    printf("The number of supported characters is: %d\n", i);
    printf("\n-----------------------------------\n");

    printf("\n");
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