#ifndef _TABLE_H
#define _TABLE_H

#include "../../manager/layout_manager/layout_manager.h"
#include "../checkbox/checkbox.h"
#include "../button/button.h"
#include "../image/image.h"
#include "../color/theme.h"
#include "../text/text.h"

typedef struct
{
    Rectangle rectangle;
    Button button;

    Checkbox checkbox;
    Image icon;

    Text filename;
    Text size;

    Text type;
    Text last_modified;

    char *path;
} Row;

typedef struct
{
    Rectangle rectangle;
    Text text;
} Column;

typedef struct
{
    Rectangle rectangle;

    int number_rows;
    Row *rows;
    int row_index;

    int number_columns;
    Column *columns;
    int column_index;

    Color background_color;
    Color text_color;
} Table;

Table construct_table(Position position, Dimension dimension, int number_rows, int number_columns, Color bacground_color, Color text_color);

void add_column(Table *table, Position position, Dimension dimension, char *text);

void add_row(Table *table, char *path, char *filename, long size, char *type, char *last_modified);

void draw_table(Table table);

#endif
