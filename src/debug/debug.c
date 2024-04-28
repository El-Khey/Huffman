#include "debug.h"

void activate_debug_mode()
{
    DEBUG = 1;
}

static int is_debug_mode()
{
    return DEBUG;
}

void debug_file_size(char *filename, int size, int flush_size)
{
    if (!is_debug_mode())
    {
        return;
    }

    printf("| Filename  | %s\n", filename);
    printf("|-----------|-----------|------------\n");
    printf("| Flush     | Size      | Total Size \n");
    printf("|-----------|-----------|------------\n");
    printf("| %d         | %d        | %d         \n\n\n", flush_size, size - flush_size, size);
}

void debug_char_frequencies(int *char_frequencies)
{
    int i;

    if (!is_debug_mode())
    {
        return;
    }

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

void debug_alphabet(Node **alphabet)
{
    if (is_debug_mode())
    {
        print_alphabet(alphabet);
    }
}
