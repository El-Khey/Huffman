#include "./utils.h"

char *convert_into_bits(int code, int size)
{
    char *bits = (char *)malloc(size + 1);
    int i;

    for (i = size - 1; i >= 0; i--)
    {
        bits[size - 1 - i] = ((code >> i) & 1) + '0';
    }

    bits[size] = '\0';
    return bits;
}

int *convert_interger_code_into_bits(int code, int size)
{
    int *bits = (int *)malloc(size + 1);
    int i;

    for (i = size - 1; i >= 0; i--)
    {
        bits[size - 1 - i] = ((code >> i) & 1);
    }

    bits[size] = '\0';
    return bits;
}

int convert_into_int(char *code, int size)
{
    int result = 0, i = 0;

    for (; i < size; i++)
    {
        if (code[i] == '1')
        {
            result |= (1 << (size - 1 - i));
        }
        else if (code[i] != '0')
        {
            fprintf(stderr, "Invalid bit string. Only '0' and '1' characters are allowed.\n");
            return -1;
        }
    }

    return result;
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
