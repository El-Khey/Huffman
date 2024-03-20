#include "./file.h"

#define MAX_SIZE 100

void read_partial_content(const char *filename)
{
    FILE *file;
    char content[MAX_SIZE];
    int read_size;

    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        exit(1);
    }

    /** Reading up to 1000 bytes from the file using fread */
    read_size = fread(content, 1, MAX_SIZE, file);

    if (read_size > 0)
    {
        printf("Partial file content (using fread):\n");
        /** Displaying the content read using fread */
        fwrite(content, 1, read_size, stdout);
    }
    else
    {
        printf("The file is empty or an error occurred while reading.\n");
    }

    fclose(file);
}

void read_full_content(const char *filename)
{
    FILE *file;
    char ch;

    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        exit(1);
    }

    printf("\n-----------------------------------\n");
    printf("\nFull file content (using fgetc):\n");

    /** Reading and displaying the content of the file using fgetc until EOF */
    while ((ch = fgetc(file)) != EOF)
    {
        putchar(ch);
    }

    fclose(file);
}
