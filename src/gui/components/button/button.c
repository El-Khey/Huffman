#include "button.h"

Button construct_button(Position position, Dimension dimension, int border_width, Color background, Color border_color)
{
    Button button;
    button.rectangle = construct_rectangle(position, dimension, border_width, background, border_color);

    return button;
}

void add_button_text(Button *button, Text text, LayoutType layout_type)
{
    button->text = text;
    button->type = BUTTON_TEXT;
    layout_manager(layout_type, &button->rectangle, &button->text.rectangle, construct_paddings(0, 0, 0, 0));
}

void add_button_image(Button *button, char *image_path)
{
    // TODO: add image to button
    button->type = BUTTON_IMAGE;
}

int is_button_hovered(Button button, Position p)
{
    return get_x(p) >= get_x(button.rectangle.position) &&
           get_x(p) <= get_x(button.rectangle.position) + get_width(button.rectangle.dimension) &&
           get_y(p) >= get_y(button.rectangle.position) &&
           get_y(p) <= get_y(button.rectangle.position) + get_height(button.rectangle.dimension);
}

void set_button_position(Button *button, Position position)
{
    button->rectangle.position = position;
}

void set_button_dimension(Button *button, Dimension dimension)
{
    button->rectangle.dimension = dimension;
}

void draw_button(Button button)
{
    draw_filled_rectangle(button.rectangle);
    (button.type == BUTTON_TEXT) ? draw_text(button.text) : draw_image(&button.image);
}