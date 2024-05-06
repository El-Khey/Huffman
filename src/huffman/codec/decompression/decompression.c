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

static int is_code_present_in_header(int *code, int size, Header header)
{
    int i;
    for (i = 0; i < MAX_CHAR; i++)
    {
        if (header.alphabet[i] != NULL && header.alphabet[i]->depth == size)
        {
            int *header_code = convert_binary_code_into_int_array(header.alphabet[i]->code, header.alphabet[i]->depth);
            if (are_arrays_equal(header_code, code, size))
            {
                free(header_code);
                return i;
            }
            free(header_code);
        }
    }

    return -1;
}

static void read_and_decode_data(FILE *file, Header header, Content *content, FILE *output)
{
    uint8_t byte;
    uint8_t bit_position = 0;

    int bit;
    int max_data_encoded_length = 50;
    int processed_length = 0, data_encoded_length = 0;
    int *data_encoded = (int *)malloc(max_data_encoded_length * sizeof(int));

    debug_current_extracted_file(content->path);
    while (processed_length < content->size - content->flush_size)
    {
        bit = read_bit(file, &byte, &bit_position);
        if (data_encoded_length >= max_data_encoded_length)
        {
            max_data_encoded_length *= 2;
            data_encoded = (int *)realloc(data_encoded, max_data_encoded_length * sizeof(int));
            printf("> Reallocating data_encoded to %d\n", max_data_encoded_length);
        }

        data_encoded[data_encoded_length] = bit;
        int index = is_code_present_in_header(data_encoded, data_encoded_length + 1, header);
        if (index != -1)
        {
            fprintf(output, "%c", header.alphabet[index]->ascii);
            processed_length += header.alphabet[index]->depth;
            data_encoded_length = 0;
        }
        else
        {
            data_encoded_length += 1;
        }
    }

    free(data_encoded);
}

static Archive read_meta(const char *filename)
{
    Archive compressed_archive;
    int i = 0, success = 0;
    int path_length = 0;
    long start_offset = 0;

    compressed_archive.file = fopen(filename, "rb");
    check_file_opening(compressed_archive.file, filename);

    compressed_archive.filename = filename;
    read_header(&compressed_archive);

    compressed_archive.content = (Content *)malloc(compressed_archive.number_of_files * sizeof(Content));
    start_offset = ftell(compressed_archive.file);
    for (; i < compressed_archive.number_of_files; i++)
    {
        success = fscanf(compressed_archive.file, "length:%d\n", &path_length);
        is_fscanf_successful(success, compressed_archive.filename);

        compressed_archive.content[i].path = (char *)malloc(path_length + 1 * sizeof(char));
        success = fscanf(compressed_archive.file, "file:%s encoded_size:%d flush_size:%d\n\n", compressed_archive.content[i].path, &compressed_archive.content[i].size, &compressed_archive.content[i].flush_size);
        is_fscanf_successful(success, compressed_archive.filename);

        compressed_archive.content[i].filename = get_filename(compressed_archive.content[i].path);

        debug_file_size(compressed_archive.content[i].path, compressed_archive.content[i].size, compressed_archive.content[i].flush_size);
        // ! NOT USED !
        // compressed_archive.content[i].encoded_data = (int *)malloc(compressed_archive.content[i].size * sizeof(int));

        // Calculate start_offset
        start_offset += path_length +
                        strlen(convert_int_into_string(compressed_archive.content[i].size)) +
                        strlen(convert_int_into_string(compressed_archive.content[i].flush_size)) +
                        strlen(convert_int_into_string(path_length)) + strlen("length:") + 1 + strlen("file: ") +
                        strlen("encoded_size: ") + strlen("flush_size:") + 1;

        compressed_archive.content[i].start_offset = start_offset;
        start_offset += compressed_archive.content[i].size % 8 == 0 ? compressed_archive.content[i].size / 8 : compressed_archive.content[i].size / 8 + 1;
        start_offset += 1; // Skip the last byte

        fseek(compressed_archive.file, start_offset, SEEK_SET); // Move to the next file
    }

    return compressed_archive;
}

void decompress(char *input_file, char *output_dir)
{
    Archive compressed_archive = read_meta(input_file);
    int i = 0;

    for (; i < compressed_archive.number_of_files; i++)
    {
        char *output_path = (char *)malloc(strlen(output_dir) + strlen(compressed_archive.content[i].path) + 1);
        fix_folder_name(output_dir);
        strcpy(output_path, output_dir);
        strcat(output_path, compressed_archive.content[i].path);

        create_intermediate_folders(output_path);
        FILE *output = fopen(output_path, "w");
        check_file_opening(output, output_path);

        fseek(compressed_archive.file, compressed_archive.content[i].start_offset, SEEK_SET);
        read_and_decode_data(compressed_archive.file, compressed_archive.header, &compressed_archive.content[i], output);

        fclose(output);
    }

    fprintf(stdout, "\n\n========================================\n");
    fprintf(stdout, "  Decompression completed successfully!\n");
    fprintf(stdout, "========================================\n\n");

    fclose(compressed_archive.file);
}
