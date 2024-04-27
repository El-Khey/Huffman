#include "table.h"

Table construct_table(Position position, Dimension dimension, int max_rows, int max_columns, Color bacground_color, Color text_color)
{
    Table table;

    table.max_rows = max_rows;
    table.rows = (Row *)malloc(max_rows * sizeof(Row));

    table.max_columns = max_columns;
    table.columns = (Column *)malloc(max_columns * sizeof(Column));

    table.background_color = bacground_color;
    table.text_color = text_color;

    table.rectangle = construct_rectangle(position, dimension, 0, TRANSPARENT_COLOR, TRANSPARENT_COLOR);
    table.rows_to_compress.total_size = 0;
    table.column_index = 0;
    table.scroll_index = 0;
    table.row_index = 0;

    table.rows_to_compress.number_saved_files = 0;
    table.rows_to_compress.max_slots = 500;
    table.rows_to_compress.list = (DocToCompress *)malloc(table.rows_to_compress.max_slots * sizeof(DocToCompress));

    return table;
}

void add_column(Table *table, Position position, Dimension dimension, char *text)
{
    if (table->column_index >= table->max_columns)
    {
        fprintf(stderr, "<warning> Table columns limit reached, maximum columns allowed: %d\n", table->max_columns);
        return;
    }

    table->columns[table->column_index].rectangle = construct_rectangle(position, dimension, 0, TRANSPARENT_COLOR, TRANSPARENT_COLOR);
    table->columns[table->column_index].text = construct_text(text, position, "assets/fonts/Roboto/Roboto-Black.ttf", 16, table->text_color);
    layout_manager(CENTER, &table->columns[table->column_index].rectangle, &table->columns[table->column_index].text.rectangle, construct_paddings(0, 0, 0, 0));
    table->column_index++;
}

static char *format_size(long size)
{
    char *size_str = (char *)malloc(100 * sizeof(char));
    double size_in_kb = size / 1024.0;
    double size_in_mb = size_in_kb / 1024.0;
    double size_in_gb = size_in_mb / 1024.0;

    if (size_in_gb >= 1.0)
    {
        sprintf(size_str, "%.2f GB", size_in_gb);
    }
    else if (size_in_mb >= 1.0)
    {
        sprintf(size_str, "%.2f MB", size_in_mb);
    }
    else if (size_in_kb >= 1.0)
    {
        sprintf(size_str, "%.2f KB", size_in_kb);
    }
    else
    {
        sprintf(size_str, "%ld B", size);
    }

    return size_str;
}

void add_row(Table *table, char *path, char *filename, long size, char *type, char *last_modified)
{
    int height = 30;
    if (table->row_index >= table->max_rows)
    {
        fprintf(stderr, "<warning> Table rows limit reached, maximum rows allowed: %d\n", table->max_rows);
        return;
    }

    int y = (table->row_index == 0) ? (get_y(table->columns[0].rectangle.position) + (table->columns[0].rectangle.dimension.height) + (table->row_index * height))
                                    : get_y(table->rows[table->row_index - 1].rectangle.position) + height;

    table->rows[table->row_index].rectangle = construct_rectangle(
        construct_position(
            get_x(table->columns[0].rectangle.position) - 25,
            y),
        construct_dimension(table->rectangle.dimension.width, height), 0,
        TRANSPARENT_COLOR, TRANSPARENT_COLOR);

    table->rows[table->row_index].button = construct_button(
        construct_position(
            get_x(table->columns[2].rectangle.position),
            y),
        construct_dimension(table->rectangle.dimension.width, height), 0, TRANSPARENT_COLOR, TRANSPARENT_COLOR);

    table->rows[table->row_index].checkbox = construct_checkbox(
        construct_position(
            get_x(table->columns[0].rectangle.position),
            get_y(table->columns[0].rectangle.position) + (table->columns[0].rectangle.dimension.height) + (table->row_index * height)),
        construct_dimension(25, 25), 3, PRIMARY_COLOR, TEXT_COLOR, SPECIAL_COLOR);
    layout_manager(VERTICAL_CENTER, &table->rows[table->row_index].rectangle, &table->rows[table->row_index].checkbox.button.rectangle, construct_paddings(0, 0, 0, 0));
    char *icon_path = (strcmp(type, "Directory") == 0) ? "assets/icons/folder.png"
                                                       : ((strcmp(type, "File") == 0) ? "assets/icons/file.png"
                                                                                      : "assets/icons/zip-compressed.png");

    table->rows[table->row_index].icon = construct_image(icon_path,
                                                         construct_position(
                                                             get_x(table->columns[2].rectangle.position),
                                                             get_y(table->columns[1].rectangle.position) + (table->columns[1].rectangle.dimension.height) + (table->row_index * height)),
                                                         construct_dimension(25, 25));
    layout_manager(VERTICAL_CENTER, &table->rows[table->row_index].rectangle, &table->rows[table->row_index].icon.rectangle, construct_paddings(0, 0, 0, 0));

    table->rows[table->row_index].path = path;
    table->rows[table->row_index].filename = construct_text(filename,
                                                            construct_position(get_x(table->columns[2].text.rectangle.position),
                                                                               get_y(table->columns[2].rectangle.position) + (table->columns[2].rectangle.dimension.height) + (table->row_index * height)),
                                                            "assets/fonts/Roboto/Roboto-Bold.ttf", 16, table->text_color);
    table->rows[table->row_index].filename.rectangle.background_color = TRANSPARENT_COLOR;
    layout_manager(VERTICAL_CENTER, &table->rows[table->row_index].rectangle, &table->rows[table->row_index].filename.rectangle, construct_paddings(0, 0, 0, 0));

    table->rows[table->row_index].size_in_bytes = size;
    table->rows[table->row_index].size = construct_text(format_size(size),
                                                        construct_position(get_x(table->columns[3].text.rectangle.position),
                                                                           get_y(table->columns[3].rectangle.position) + (table->columns[3].rectangle.dimension.height) + (table->row_index * height)),
                                                        "assets/fonts/Roboto/Roboto-Bold.ttf", 16, table->text_color);
    layout_manager(VERTICAL_CENTER, &table->rows[table->row_index].rectangle, &table->rows[table->row_index].size.rectangle, construct_paddings(0, 0, 0, 0));

    table->rows[table->row_index].type = construct_text(type,
                                                        construct_position(get_x(table->columns[4].text.rectangle.position),
                                                                           get_y(table->columns[4].rectangle.position) + (table->columns[4].rectangle.dimension.height) + (table->row_index * height)),
                                                        "assets/fonts/Roboto/Roboto-Bold.ttf", 16, table->text_color);
    layout_manager(VERTICAL_CENTER, &table->rows[table->row_index].rectangle, &table->rows[table->row_index].type.rectangle, construct_paddings(0, 0, 0, 0));

    table->rows[table->row_index].last_modified = construct_text(last_modified,
                                                                 construct_position(get_x(table->columns[5].text.rectangle.position),
                                                                                    get_y(table->columns[5].rectangle.position) + (table->columns[5].rectangle.dimension.height) + (table->row_index * height)),
                                                                 "assets/fonts/Roboto/Roboto-Bold.ttf", 16, table->text_color);
    layout_manager(VERTICAL_CENTER, &table->rows[table->row_index].rectangle, &table->rows[table->row_index].last_modified.rectangle, construct_paddings(0, 0, 0, 0));
    table->row_index++;
}

static void remove_row_to_compress(Table *table, char *path, long size)
{
    int i = 0;
    for (; i < table->rows_to_compress.number_saved_files; i++)
    {
        if (strcmp(table->rows_to_compress.list[i].path, path) == 0)
        {
            break;
        }
    }

    for (; i < table->rows_to_compress.number_saved_files - 1; i++)
    {
        table->rows_to_compress.list[i] = table->rows_to_compress.list[i + 1];
    }

    table->rows_to_compress.total_size -= size;
    table->rows_to_compress.number_saved_files--;
}

static void save_row_to_compress(Table *table, char *path, long size)
{
    table->rows_to_compress.list[table->rows_to_compress.number_saved_files].path = path;
    table->rows_to_compress.total_size += size;
    table->rows_to_compress.number_saved_files++;
}

void clear_table_rows(Table *table)
{
    for (int i = 0; i < table->row_index; i++)
    {
        free_text(&table->rows[i].filename);
        free_text(&table->rows[i].size);
        free_text(&table->rows[i].type);
        free_text(&table->rows[i].last_modified);
        free_image(&table->rows[i].icon);
    }

    free(table->rows);
    table->row_index = 0;
    table->rows = (Row *)malloc(table->max_rows * sizeof(Row));
}

void handle_table_selection(Table *table, MouseManager mouse_manager)
{
    int i = 0;
    for (; i < table->row_index; i++)
    {
        if (is_button_clicked(table->rows[i].checkbox.button, mouse_manager))
        {
            check(&table->rows[i].checkbox);
            (table->rows[i].checkbox.is_checked) ? save_row_to_compress(table, table->rows[i].path, table->rows[i].size_in_bytes)
                                                 : remove_row_to_compress(table, table->rows[i].path, table->rows[i].size_in_bytes);
        }
    }
}

void deselect_all(Table *table)
{
    int i = 0;
    table->rows_to_compress.total_size = 0;
    table->rows_to_compress.number_saved_files = 0;

    for (; i < table->row_index; i++)
    {
        uncheck(&table->rows[i].checkbox);
    }
}

static void draw_columns(Column *columns, int max_columns)
{
    for (int i = 0; i < max_columns; i++)
    {
        draw_filled_rectangle(columns[i].rectangle);
        draw_text(columns[i].text);
    }
}

static void draw_rows(Row *rows, int max_rows)
{
    for (int i = 0; i < max_rows; i++)
    {
        draw_filled_rectangle(rows[i].rectangle);
        draw_button(rows[i].button);
        draw_checkbox(rows[i].checkbox);
        draw_image(&rows[i].icon);
        draw_text(rows[i].filename);
        draw_text(rows[i].size);
        draw_text(rows[i].type);
        draw_text(rows[i].last_modified);
    }
}

void draw_table(Table table)
{
    draw_filled_rectangle(table.rectangle);

    draw_columns(table.columns, table.max_columns);
    draw_rows(table.rows, table.row_index);
}