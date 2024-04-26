#include "text.h"

Text construct_text(char *text, Position position, char *font_path, int font_size, Color color)
{
    Text t;

    t.text = (char *)malloc(strlen(text) + 1);
    strcpy(t.text, text);

    t.font_path = font_path;
    t.font_size = font_size;

    t.color = color;

    MLV_get_size_of_text_with_font(t.text, &t.rectangle.dimension.width, &t.rectangle.dimension.height, MLV_load_font(font_path, font_size));
    t.rectangle = construct_rectangle(position, t.rectangle.dimension, 0, TRANSPARENT_COLOR, TRANSPARENT_COLOR);

    t.font = MLV_load_font(t.font_path, t.font_size);

    return t;
}

void set_text_content(Text *text, char *content)
{
    free(text->text);

    text->text = (char *)malloc(strlen(content) + 1);
    strcpy(text->text, content);

    MLV_get_size_of_text_with_font(text->text, &text->rectangle.dimension.width, &text->rectangle.dimension.height, text->font);
}

void set_text_position(Text *text, Position position)
{
    text->rectangle.position = position;
}

void set_text_dimensions(Text *text, Dimension dimension)
{
    text->rectangle.dimension = dimension;
}

int get_text_width(Text text)
{
    return text.rectangle.dimension.width;
}

int get_text_height(Text text)
{
    return text.rectangle.dimension.height;
}

void draw_text(Text text)
{
    draw_filled_rectangle(text.rectangle);
    MLV_draw_text_with_font(
        get_x(text.rectangle.position),
        get_y(text.rectangle.position),
        text.text,
        text.font,
        convert_color(text.color));
}

void draw_text_with_shadow(Text text, int shadow_offset)
{
    MLV_draw_text_with_font(
        get_x(text.rectangle.position) + shadow_offset,
        get_y(text.rectangle.position) + shadow_offset,
        text.text,
        text.font,
        MLV_COLOR_BLACK);

    MLV_draw_text_with_font(
        get_x(text.rectangle.position),
        get_y(text.rectangle.position),
        text.text,
        text.font,
        convert_color(text.color));
}

void free_text(Text *text)
{
    MLV_free_font(text->font);
    free(text->text);

    text->font = NULL;
    text->text = NULL;
}