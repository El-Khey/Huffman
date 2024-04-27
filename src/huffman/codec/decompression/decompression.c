#include "decompression.h"

static void read_header(Archive *compressed_archive)
{
    int i, frequency, size, success, ascii;
    char binary_code[MAX_CHAR];
    int *code;

    success = fscanf(compressed_archive->file, "%d\n", &compressed_archive->header.number_of_leaves);
    is_fscanf_successful(success, compressed_archive->filename);

    for (i = 0; i < MAX_CHAR; i++)
    {
        if (i < compressed_archive->header.number_of_leaves)
        {
            success = fscanf(compressed_archive->file, "%d %d %d %s\n", &ascii, &frequency, &size, binary_code);
            is_fscanf_successful(success, compressed_archive->filename);

            code = (int *)malloc(size * sizeof(int));
            code = convert_string_into_code(binary_code, size);

            int code_value = convert_int_array_into_int(code, size);
            compressed_archive->header.alphabet[i] = create_node(ascii, frequency, size, code_value);
        }
        else
        {
            compressed_archive->header.alphabet[i] = NULL;
        }
    }

    success = fscanf(compressed_archive->file, "n:%d\n", &compressed_archive->number_of_files);
    is_fscanf_successful(success, compressed_archive->filename);
}

static void read_encoded_data(FILE *file, Content *content)
{
    uint8_t bit_position = 0;
    uint8_t byte = 0;
    int bit, i = 0;

    while ((bit = read_bit(file, &byte, &bit_position)) != -1)
    {
        if (i >= content->size)
        {
            break;
        }

        content->encoded_data[i] = bit;
        i++;
    }
}

static Archive read_meta(const char *filename)
{
    Archive compressed_archive;
    int i = 0, success = 0;
    int path_length = 0;

    compressed_archive.file = fopen(filename, "rb");
    check_file_opening(compressed_archive.file, filename);

    compressed_archive.filename = filename;
    read_header(&compressed_archive);

    compressed_archive.content = (Content *)malloc(compressed_archive.number_of_files * sizeof(Content));

    for (; i < compressed_archive.number_of_files; i++)
    {
        success = fscanf(compressed_archive.file, "length:%d\n", &path_length);
        is_fscanf_successful(success, compressed_archive.filename);

        compressed_archive.content[i].path = (char *)malloc(path_length + 1 * sizeof(char));
        success = fscanf(compressed_archive.file, "file:%s encoded_size:%d flush_size:%d\n\n", compressed_archive.content[i].path, &compressed_archive.content[i].size, &compressed_archive.content[i].flush_size);
        is_fscanf_successful(success, compressed_archive.filename);

        compressed_archive.content[i].filename = get_filename(compressed_archive.content[i].path);

        // debug_file_size(compressed_archive.content[i].path, compressed_archive.content[i].size, compressed_archive.content[i].flush_size); // ! TODO: use a debug flag to trigger this line
        compressed_archive.content[i].encoded_data = (int *)malloc(compressed_archive.content[i].size * sizeof(int));
        read_encoded_data(compressed_archive.file, &compressed_archive.content[i]);
    }

    return compressed_archive;
}

static void decode(Header header, Content content, FILE *output)
{
    int processed_length = 0;
    int i = 0, index = 0;
    int code_found = 1;

    while (1)
    {
        index = (i % MAX_CHAR);

        if (header.alphabet[index] == NULL)
        {
            i++;
            continue;
        }

        if (processed_length >= content.size - content.flush_size)
        {
            break;
        }

        code_found = 1;
        int *code = convert_binary_code_into_int_array(header.alphabet[index]->code, header.alphabet[index]->depth);
        code_found = are_arrays_equal(code, content.encoded_data, processed_length, header.alphabet[index]->depth);

        if (code_found)
        {
            fprintf(output, "%c", header.alphabet[index]->ascii);
            processed_length += header.alphabet[index]->depth;
        }

        i++;
    }
}

void decompress(char *input_file, char *output_dir)
{
    Archive compressed_archive = read_meta(input_file);
    int i = 0;

    create_folder(output_dir);
    for (; i < compressed_archive.number_of_files; i++)
    {
        char *output_path = (char *)malloc(strlen(output_dir) + strlen(compressed_archive.content[i].path) + 1);
        strcpy(output_path, output_dir);
        strcat(output_path, compressed_archive.content[i].path);

        create_intermediate_folders(output_path);
        FILE *output = fopen(output_path, "w");
        check_file_opening(output, output_path);

        decode(compressed_archive.header, compressed_archive.content[i], output);
        fclose(output);
    }

    fprintf(stdout, "\n\n========================================\n");
    fprintf(stdout, "  Decompression completed successfully!\n");
    fprintf(stdout, "========================================\n\n");

    fclose(compressed_archive.file);
}