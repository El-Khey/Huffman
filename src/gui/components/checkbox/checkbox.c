#include "checkbox.h"

Checkbox construct_checkbox(Position position, Dimension dimension, int border_width, Color default_color, Color border_color, Color checked_color)
{
    Checkbox checkbox;

    checkbox.is_checked = 0;
    checkbox.checked_color = checked_color;
    checkbox.default_color = default_color;

    checkbox.button = construct_button(position, dimension, border_width, default_color, border_color);

    add_border_to_rectangle(&checkbox.button.rectangle, BORDER_TOP, border_width, border_color);
    add_border_to_rectangle(&checkbox.button.rectangle, BORDER_BOTTOM, border_width, border_color);
    add_border_to_rectangle(&checkbox.button.rectangle, BORDER_LEFT, border_width, border_color);
    add_border_to_rectangle(&checkbox.button.rectangle, BORDER_RIGHT, border_width, border_color);

    return checkbox;
}

void check(Checkbox *checkbox)
{
    checkbox->is_checked = !checkbox->is_checked;
    checkbox->button.rectangle.background_color = (checkbox->is_checked) ? checkbox->checked_color : checkbox->default_color;
}

void draw_checkbox(Checkbox checkbox)
{
    draw_button(checkbox.button);
}