#include "rectangle.h"

Rectangle construct_rectangle(Position position, Dimension dimension, int border_width, Color background, Color border_color)
{
    Rectangle rectangle;
    int i = 0;

    rectangle.position = position;
    rectangle.dimension = dimension;
    rectangle.border_width = border_width;
    rectangle.background_color = background;
    rectangle.border_color = border_color;

    for (; i < num_borders; i++)
    {
        rectangle.borders[i].is_visible = 0;
        rectangle.borders[i].border_width = border_width;
        rectangle.borders[i].border_color = border_color;
    }

    return rectangle;
}

int is_rectangle_hovered(Rectangle rectangle, Position p)
{
    return get_x(p) >= get_x(rectangle.position) &&
           get_x(p) <= get_x(rectangle.position) + get_width(rectangle.dimension) &&
           get_y(p) >= get_y(rectangle.position) &&
           get_y(p) <= get_y(rectangle.position) + get_height(rectangle.dimension);
}

void add_border_to_rectangle(Rectangle *rectangle, BorderType border_type, int border_width, Color border_color)
{
    rectangle->borders[border_type].is_visible = 1;
    rectangle->borders[border_type].border_width = border_width;
    rectangle->borders[border_type].border_color = border_color;
}

static void draw_border_top(Rectangle rectangle)
{
    MLV_Color border_color = convert_color(rectangle.borders[BORDER_TOP].border_color);
    MLV_draw_filled_rectangle(get_x(rectangle.position), get_y(rectangle.position), get_width(rectangle.dimension), rectangle.borders[BORDER_TOP].border_width, border_color);
}

static void draw_border_right(Rectangle rectangle)
{
    MLV_Color border_color = convert_color(rectangle.borders[BORDER_RIGHT].border_color);
    MLV_draw_filled_rectangle(get_x(rectangle.position) + get_width(rectangle.dimension) - rectangle.borders[BORDER_RIGHT].border_width, get_y(rectangle.position), rectangle.borders[BORDER_RIGHT].border_width, get_height(rectangle.dimension), border_color);
}

static void draw_border_bottom(Rectangle rectangle)
{
    MLV_Color border_color = convert_color(rectangle.borders[BORDER_BOTTOM].border_color);
    MLV_draw_filled_rectangle(get_x(rectangle.position), get_y(rectangle.position) + get_height(rectangle.dimension) - rectangle.borders[BORDER_BOTTOM].border_width, get_width(rectangle.dimension), rectangle.borders[BORDER_BOTTOM].border_width, border_color);
}

static void draw_border_left(Rectangle rectangle)
{
    MLV_Color border_color = convert_color(rectangle.borders[BORDER_LEFT].border_color);
    MLV_draw_filled_rectangle(get_x(rectangle.position), get_y(rectangle.position), rectangle.borders[BORDER_LEFT].border_width, get_height(rectangle.dimension), border_color);
}

static void draw_rectangle_border(Rectangle rectangle)
{
    int i = 0;
    for (; i < num_borders; i++)
    {
        if (rectangle.borders[i].is_visible)
        {
            switch (i)
            {
            case BORDER_TOP:
                draw_border_top(rectangle);
                break;
            case BORDER_RIGHT:
                draw_border_right(rectangle);
                break;
            case BORDER_BOTTOM:
                draw_border_bottom(rectangle);
                break;
            case BORDER_LEFT:
                draw_border_left(rectangle);
                break;
            default:
                break;
            }
        }
    }
}

void draw_filled_rectangle(Rectangle rectangle)
{
    MLV_draw_filled_rectangle(
        get_x(rectangle.position),
        get_y(rectangle.position),
        get_width(rectangle.dimension),
        get_height(rectangle.dimension),
        convert_color(rectangle.background_color));

    draw_rectangle_border(rectangle);
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
