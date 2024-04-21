#include "button.h"

Button construct_button_with_image(Image image, Position position, Dimension dimension)
{
    Button button;

    button.image = image;
    set_image_position(&button.image, position);

    button.position = position;
    button.dimension = dimension;

    return button;
}

Button construct_button_with_text(char *text, Position position, Dimension dimension, MLV_Color foreground, MLV_Color background)
{
    Button button;
    Text t = construct_text(text, position, "assets/fonts/Play-Bold.ttf", 20, foreground);
    set_text_position(
        &t,
        construct_position(get_x(position) + (get_width(dimension) - get_text_width(t)) / 2,
                           get_y(position) + (get_height(dimension) - get_text_height(t)) / 2));

    button.position = position;
    button.dimension = dimension;
    button.text = t;

    button.background = background;
    button.foreground = foreground;

    return button;
}

void set_button_position(Button *button, Position position)
{
    button->position = position;
}

void set_button_dimension(Button *button, Dimension dimension)
{
    button->dimension = dimension;
}

void draw_filled_button_with_hover_effect(Button button, Position mouse_position, MLV_Color border_color, MLV_Color background)
{
    if (is_button_hovered(button, mouse_position))
    {
        draw_filled_rectangle(button.position, button.dimension, 2, border_color, background);
    }
    else
    {
        draw_filled_rectangle(button.position, button.dimension, 2, button.background, button.background);
    }

    draw_button_text(button);
}

void draw_hovered_button(Button button, Position mouse_position, MLV_Color border_color, MLV_Color background)
{
    if (is_button_hovered(button, mouse_position))
    {
        draw_filled_rectangle(button.position, button.dimension, 2, border_color, background);
    }
    else
    {
        draw_filled_rectangle(button.position, button.dimension, 2, button.background, button.background);
    }
}

int is_button_hovered(Button button, Position p)
{
    return get_x(p) >= get_x(button.position) &&
           get_x(p) <= get_x(button.position) + get_width(button.dimension) &&
           get_y(p) >= get_y(button.position) &&
           get_y(p) <= get_y(button.position) + get_height(button.dimension);
}

int is_button_clicked(Button button, MouseManager mouse_manager)
{
    return is_button_hovered(button, get_mouse_position(mouse_manager)) && is_left_button_clicked(mouse_manager);
}

void draw_button_image(Button button)
{
    draw_image(&button.image);
}

void draw_button_text(Button button)
{
    draw_text(button.text);
}

void free_button_image(Button *button)
{
    free_image(&button->image);
}

void free_button_text(Button *button)
{
    free_text(&button->text);
}