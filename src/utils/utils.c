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
