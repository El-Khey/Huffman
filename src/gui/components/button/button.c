#include "button.h"

Button construct_button(Position position, Dimension dimension, int border_width, Color background, Color border_color)
{
    Button button;
    button.rectangle = construct_rectangle(position, dimension, border_width, background, border_color);

    return button;
}

void add_button_text(Button *button, char *text, char *font_path, int font_size, Color color)
{
    // TODO: add text to button center it
}

void add_button_image(Button *button, char *image_path)
{
    // TODO: add image to button
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

// void draw_filled_button_with_hover_effect(Button button, Position mouse_position, Color border_color)
// {
//     if (is_button_hovered(button, mouse_position))
//     {
//         draw_filled_rectangle_with_border(button.rectangle, 2, border_color);
//     }
//     else
//     {
//         draw_filled_rectangle_with_border(button.rectangle, 2, button.background);
//     }

//     draw_button_text(button);
// }

// void draw_hovered_button(Button button, Position mouse_position, MLV_Color border_color, MLV_Color background)
// {
//     if (is_button_hovered(button, mouse_position))
//     {
//         draw_filled_rectangle(button.position, button.dimension, 2, border_color, background);
//     }
//     else
//     {
//         draw_filled_rectangle(button.position, button.dimension, 2, button.background, button.background);
//     }
// }

// int is_button_clicked(Button button, MouseManager mouse_manager)
// {
//     return is_button_hovered(button, get_mouse_position(mouse_manager)) && is_left_button_clicked(mouse_manager);
// }

// void draw_button_image(Button button)
// {
//     draw_image(&button.image);
// }

// void draw_button_text(Button button)
// {
//     draw_text(button.text);
// }

// void free_button_image(Button *button)
// {
//     free_image(&button->image);
// }

// void free_button_text(Button *button)
// {
//     free_text(&button->text);
// }