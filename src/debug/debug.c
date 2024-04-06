#include "debug.h"

void debug_file_size(char *filename, int size, int flush_size)
{
    printf("| Filename  | %s\n", filename);
    printf("|-----------|-----------|------------\n");
    printf("| Flush     | Size      | Total Size \n");
    printf("|-----------|-----------|------------\n");
    printf("| %d         | %d        | %d         \n\n\n", flush_size, size, size + flush_size);
}
