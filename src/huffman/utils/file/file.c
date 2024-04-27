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

    /** Reading up to 1000 B from the file using fread */
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

void check_file_opening(FILE *file, const char *filename)
{
    if (file == NULL)
    {
        fprintf(stderr, "----------------------------------------------\n");
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        fprintf(stderr, "----------------------------------------------\n");
        exit(EXIT_FAILURE);
    }
}

void prompt_override_existing_file(FILE *file, const char *filename)
{
    char response;
    int success;

    if (file)
    {
        fprintf(stderr, "\n----------------------------------------------\n");
        fprintf(stderr, "/!\\ The file %s already exists.\n", filename);
        fprintf(stderr, "\n----------------------------------------------\n");

        printf("Do you want to override the file? (y/n): ");
        success = scanf(" %c", &response);

        if (success != 1)
        {
            fprintf(stderr, "Error: Could not read the response.\n");
            exit(EXIT_FAILURE);
        }

        if (response == 'n' || response == 'N')
        {
            fprintf(stderr, "> Exiting...\n");
            exit(EXIT_FAILURE);
        }
    }
}

void is_fscanf_successful(int success, const char *filename)
{
    if (!success)
    {
        fprintf(stderr, "Error: could not read the file. Scanf failed.\n");
        fprintf(stderr, "File: %s\n", filename);
        exit(EXIT_FAILURE);
    }
}

char *get_filename(const char *path)
{
    char *filename = strrchr(path, '/');
    if (filename == NULL)
    {
        return (char *)path;
    }
    else
    {
        return filename + 1;
    }
}

int is_text_file(const char *filename)
{
    return strstr(filename, ".txt") != NULL;
}

int is_archive_file(const char *filename)
{
    return strstr(filename, ".bin") != NULL;
}