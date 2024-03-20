#include "./utils.h"

void count_char_frequencies(FILE *file, int tab[MAX_CHAR])
{
    int ch;
    int i;

    /** Initialize the array with zeros */
    for (i = 0; i < MAX_CHAR; i++)
    {
        tab[i] = 0;
    }

    /** Count occurrences of each character */
    while ((ch = fgetc(file)) != EOF)
    {
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

    printf("The number of characters in the file is: %d\n", i);
    printf("\n-----------------------------------\n");

    printf("\n");
}
