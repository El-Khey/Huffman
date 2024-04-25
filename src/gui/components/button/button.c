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

void add_button_image(Button *button, Image image, LayoutType layout_type)
{
    button->image = image;
    button->type = BUTTON_IMAGE;
    layout_manager(layout_type, &button->rectangle, &button->image.rectangle, construct_paddings(0, 0, 0, 0));
}

int is_button_hovered(Button button, Position p)
{
    return get_x(p) >= get_x(button.rectangle.position) &&
           get_x(p) <= get_x(button.rectangle.position) + get_width(button.rectangle.dimension) &&
           get_y(p) >= get_y(button.rectangle.position) &&
           get_y(p) <= get_y(button.rectangle.position) + get_height(button.rectangle.dimension);
}

int is_button_clicked(Button button, MouseManager mouse_manager)
{
    return is_button_hovered(button, get_mouse_position(mouse_manager)) && is_left_button_clicked(mouse_manager);
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

    if (button.type == BUTTON_TEXT)
    {
        draw_text(button.text);
    }
    else if (button.type == BUTTON_IMAGE)
    {
        draw_image(&button.image);
    }
}