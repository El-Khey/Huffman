#include "text.h"

Text construct_text(char *text, Position position, char *font_path, int font_size, MLV_Color color)
{
    Text t;

    t.text = (char *)malloc(strlen(text) + 1);
    strcpy(t.text, text);

    t.position = position;

    t.font_path = font_path;
    t.font_size = font_size;

    t.color = color;

    MLV_get_size_of_text_with_font(t.text, &t.dimension.width, &t.dimension.height, MLV_load_font(font_path, font_size));
    t.font = MLV_load_font(t.font_path, t.font_size);

    return t;
}

void set_text_content(Text *text, char *content)
{
    free(text->text);

    text->text = (char *)malloc(strlen(content) + 1);
    strcpy(text->text, content);

    MLV_get_size_of_text_with_font(text->text, &text->dimension.width, &text->dimension.height, text->font);
}

void set_text_position(Text *text, Position position)
{
    text->position = position;
}

int get_text_width(Text text)
{
    return text.dimension.width;
}

int get_text_height(Text text)
{
    return text.dimension.height;
}

void draw_text(Text text)
{
    MLV_draw_text_with_font(
        get_x(text.position),
        get_y(text.position),
        text.text,
        text.font,
        text.color);
}

void draw_text_with_shadow(Text text, int shadow_offset)
{
    MLV_draw_text_with_font(
        get_x(text.position) + shadow_offset,
        get_y(text.position) + shadow_offset,
        text.text,
        text.font,
        MLV_COLOR_BLACK);

    MLV_draw_text_with_font(
        get_x(text.position),
        get_y(text.position),
        text.text,
        text.font,
        text.color);
}

void free_text(Text *text)
{
    MLV_free_font(text->font);
    free(text->text);

    text->font = NULL;
    text->text = NULL;
}