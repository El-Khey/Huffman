#include "table.h"

Table construct_table(Position position, Dimension dimension, int number_rows, int number_columns, Color bacground_color, Color text_color)
{
    Table table;

    table.number_rows = number_rows;
    table.rows = (Row *)malloc(number_rows * sizeof(Row));

    table.number_columns = number_columns;
    table.columns = (Column *)malloc(number_columns * sizeof(Column));

    table.background_color = bacground_color;
    table.text_color = text_color;

    table.rectangle = construct_rectangle(position, dimension, 0, TRANSPARENT_COLOR, TRANSPARENT_COLOR);
    table.column_index = 0;
    table.row_index = 0;

    return table;
}

void add_column(Table *table, Position position, Dimension dimension, char *text)
{
    if (table->column_index >= table->number_columns)
    {
        fprintf(stderr, "<warning> Table columns limit reached, maximum columns allowed: %d\n", table->number_columns);
        return;
    }

    table->columns[table->column_index].rectangle = construct_rectangle(position, dimension, 0, TRANSPARENT_COLOR, TRANSPARENT_COLOR);
    table->columns[table->column_index].text = construct_text(text, position, "assets/fonts/Roboto/Roboto-Black.ttf", 16, table->text_color);
    layout_manager(CENTER, &table->columns[table->column_index].rectangle, &table->columns[table->column_index].text.rectangle, construct_paddings(0, 0, 0, 0));
    table->column_index++;
}

void add_row(Table *table, char *path, char *filename, long size, char *type, char *last_modified)
{
    int height = 30;

    if (table->row_index >= table->number_rows)
    {
        fprintf(stderr, "<warning> Table rows limit reached, maximum rows allowed: %d\n", table->number_rows);
        return;
    }

    int y = (table->row_index == 0) ? (get_y(table->columns[0].rectangle.position) + (table->columns[0].rectangle.dimension.height) + (table->row_index * height))
                                    : get_y(table->rows[table->row_index - 1].rectangle.position) + height;

    table->rows[table->row_index].rectangle = construct_rectangle(
        construct_position(
            get_x(table->columns[0].rectangle.position) - 25,
            y + 2),
        construct_dimension(table->rectangle.dimension.width, height), 0,
        TRANSPARENT_COLOR, TRANSPARENT_COLOR);

    table->rows[table->row_index].checkbox = construct_checkbox(
        construct_position(
            get_x(table->columns[0].rectangle.position),
            get_y(table->columns[0].rectangle.position) + (table->columns[0].rectangle.dimension.height) + (table->row_index * height)),
        construct_dimension(25, 25), 3, LIGHT_COLOR, DARK_COLOR, construct_color(1, 0, 0, 1));
    layout_manager(VERTICAL_CENTER, &table->rows[table->row_index].rectangle, &table->rows[table->row_index].checkbox.button.rectangle, construct_paddings(0, 0, 0, 0));

    char *icon_path = (strcmp(type, "Directory") == 0) ? "assets/icons/folder.png" : "assets/icons/file.png";
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
                                                            "assets/fonts/Roboto/Roboto-Regular.ttf", 16, table->text_color);
    table->rows[table->row_index].filename.rectangle.background_color = TRANSPARENT_COLOR;
    layout_manager(VERTICAL_CENTER, &table->rows[table->row_index].rectangle, &table->rows[table->row_index].filename.rectangle, construct_paddings(0, 0, 0, 0));

    char size_str[100];
    sprintf(size_str, "%ld", size);
    table->rows[table->row_index].size = construct_text(size_str,
                                                        construct_position(get_x(table->columns[3].text.rectangle.position),
                                                                           get_y(table->columns[3].rectangle.position) + (table->columns[3].rectangle.dimension.height) + (table->row_index * height)),
                                                        "assets/fonts/Roboto/Roboto-Regular.ttf", 16, table->text_color);
    layout_manager(VERTICAL_CENTER, &table->rows[table->row_index].rectangle, &table->rows[table->row_index].size.rectangle, construct_paddings(0, 0, 0, 0));

    table->rows[table->row_index].type = construct_text(type,
                                                        construct_position(get_x(table->columns[4].text.rectangle.position),
                                                                           get_y(table->columns[4].rectangle.position) + (table->columns[4].rectangle.dimension.height) + (table->row_index * height)),
                                                        "assets/fonts/Roboto/Roboto-Regular.ttf", 16, table->text_color);
    layout_manager(VERTICAL_CENTER, &table->rows[table->row_index].rectangle, &table->rows[table->row_index].type.rectangle, construct_paddings(0, 0, 0, 0));

    table->rows[table->row_index].last_modified = construct_text(last_modified,
                                                                 construct_position(get_x(table->columns[5].text.rectangle.position),
                                                                                    get_y(table->columns[5].rectangle.position) + (table->columns[5].rectangle.dimension.height) + (table->row_index * height)),
                                                                 "assets/fonts/Roboto/Roboto-Regular.ttf", 16, table->text_color);
    layout_manager(VERTICAL_CENTER, &table->rows[table->row_index].rectangle, &table->rows[table->row_index].last_modified.rectangle, construct_paddings(0, 0, 0, 0));

    table->row_index++;
}

void handle_table_selection(Table *table, MouseManager mouse_manager)
{
    int i = 0;
    for (; i < table->row_index; i++)
    {
        if (is_button_clicked(table->rows[i].checkbox.button, mouse_manager))
        {
            check(&table->rows[i].checkbox);
        }
    }
}

static void draw_columns(Column *columns, int number_columns)
{
    for (int i = 0; i < number_columns; i++)
    {
        draw_filled_rectangle(columns[i].rectangle);
        draw_text(columns[i].text);
    }
}

static void draw_rows(Row *rows, int number_rows)
{
    for (int i = 0; i < number_rows; i++)
    {
        draw_filled_rectangle(rows[i].rectangle);
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

    draw_columns(table.columns, table.number_columns);
    draw_rows(table.rows, table.row_index);
}