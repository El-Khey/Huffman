#include "rectangle.h"

Rectangle construct_rectangle(Position position, Dimension dimension, int border_width, Color background, Color border_color)
{
    Rectangle rectangle;

    rectangle.position = position;
    rectangle.dimension = dimension;
    rectangle.border_width = border_width;
    rectangle.background_color = background;
    rectangle.border_color = border_color;

    return rectangle;
}

static void draw_rectangle_border(Rectangle rectangle)
{
    MLV_Color border_color = convert_color(rectangle.border_color);
    MLV_draw_filled_rectangle(get_x(rectangle.position), get_y(rectangle.position), get_width(rectangle.dimension), rectangle.border_width, border_color);
    MLV_draw_filled_rectangle(get_x(rectangle.position), get_y(rectangle.position), rectangle.border_width, get_height(rectangle.dimension), border_color);
    MLV_draw_filled_rectangle(get_x(rectangle.position) + get_width(rectangle.dimension) - rectangle.border_width, get_y(rectangle.position), rectangle.border_width, get_height(rectangle.dimension), border_color);
    MLV_draw_filled_rectangle(get_x(rectangle.position), get_y(rectangle.position) + get_height(rectangle.dimension) - rectangle.border_width, get_width(rectangle.dimension), rectangle.border_width, border_color);
}

void draw_filled_rectangle(Rectangle rectangle)
{
    MLV_draw_filled_rectangle(
        get_x(rectangle.position),
        get_y(rectangle.position),
        get_width(rectangle.dimension),
        get_height(rectangle.dimension),
        convert_color(rectangle.background_color));
}

void draw_rectangle_outline(Rectangle rectangle)
{
    MLV_draw_rectangle(
        get_x(rectangle.position),
        get_y(rectangle.position),
        get_width(rectangle.dimension),
        get_height(rectangle.dimension),
        convert_color(rectangle.background_color));
}

void draw_filled_rectangle_with_border(Rectangle rectangle)
{
    MLV_draw_filled_rectangle(get_x(rectangle.position),
                              get_y(rectangle.position),
                              get_width(rectangle.dimension),
                              get_height(rectangle.dimension),
                              convert_color(rectangle.background_color));
    draw_rectangle_border(rectangle);
}