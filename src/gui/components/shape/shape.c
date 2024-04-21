#include "shape.h"

Rectangle construct_rectangle(Position position, Dimension dimension, MLV_Color color)
{
    Rectangle rectangle;

    rectangle.position = position;
    rectangle.dimension = dimension;
    rectangle.color = color;

    return rectangle;
}

void draw_rectangle(Rectangle rectangle)
{
    MLV_draw_filled_rectangle(get_x(rectangle.position), get_y(rectangle.position), get_width(rectangle.dimension), get_height(rectangle.dimension), rectangle.color);
}

void draw_gradient_rectangle(Position position1, Position position2, MLV_Color color1, MLV_Color color2)
{
    int i, j;

    int x1 = get_x(position1);
    int y1 = get_y(position1);

    int x2 = get_x(position2);
    int y2 = get_y(position2);

    for (i = x1; i < x2; i++)
    {
        for (j = y1; j < y2; j++)
        {
            double t = (double)(i - x1) / (x2 - x1);
            Uint8 r1, g1, b1, a1;
            Uint8 r2, g2, b2, a2;
            Uint8 r, g, b, a;

            MLV_Color gradient_color;

            MLV_convert_color_to_rgba(color1, &r1, &g1, &b1, &a1);
            MLV_convert_color_to_rgba(color2, &r2, &g2, &b2, &a2);

            r = (Uint8)(r1 + t * (r2 - r1));
            g = (Uint8)(g1 + t * (g2 - g1));
            b = (Uint8)(b1 + t * (b2 - b1));
            a = (Uint8)(a1 + t * (a2 - a1));

            gradient_color = MLV_rgba(r, g, b, a);
            MLV_draw_pixel(i, j, gradient_color);
        }
    }
}

void draw_vertical_gradient_rectangle(Position position1, Position position2, MLV_Color color1, MLV_Color color2)
{
    int i, j;

    int x1 = get_x(position1);
    int y1 = get_y(position1);

    int x2 = get_x(position2);
    int y2 = get_y(position2);

    for (i = x1; i < x2; i++)
    {
        for (j = y1; j < y2; j++)
        {
            double t = (double)(j - y1) / (y2 - y1);
            Uint8 r1, g1, b1, a1;
            Uint8 r2, g2, b2, a2;
            Uint8 r, g, b, a;
            MLV_Color gradient_color;

            MLV_convert_color_to_rgba(color1, &r1, &g1, &b1, &a1);
            MLV_convert_color_to_rgba(color2, &r2, &g2, &b2, &a2);

            r = (Uint8)(r1 + t * (r2 - r1));
            g = (Uint8)(g1 + t * (g2 - g1));
            b = (Uint8)(b1 + t * (b2 - b1));
            a = (Uint8)(a1 + t * (a2 - a1));

            gradient_color = MLV_rgba(r, g, b, a);
            MLV_draw_pixel(i, j, gradient_color);
        }
    }
}

void draw_rounded_filled_rectangle(Position position, Dimension dimension, int corner_radius, MLV_Color color)
{
    /** Draw the main filled rectangle */
    MLV_draw_filled_rectangle(get_x(position) + corner_radius, get_y(position), get_width(dimension) - 2 * corner_radius, get_height(dimension), color);
    MLV_draw_filled_rectangle(get_x(position), get_y(position) + corner_radius, get_width(dimension), get_height(dimension) - 2 * corner_radius, color);

    /** Draw the rounded corners */
    MLV_draw_filled_circle(get_x(position) + corner_radius, get_y(position) + corner_radius, corner_radius, color);
    MLV_draw_filled_circle(get_x(position) + get_width(dimension) - corner_radius, get_y(position) + corner_radius, corner_radius, color);
    MLV_draw_filled_circle(get_x(position) + corner_radius, get_y(position) + get_height(dimension) - corner_radius, corner_radius, color);
    MLV_draw_filled_circle(get_x(position) + get_width(dimension) - corner_radius, get_y(position) + get_height(dimension) - corner_radius, corner_radius, color);
}

void draw_border(Position position, Dimension dimension, int border_width, MLV_Color color)
{
    MLV_draw_filled_rectangle(get_x(position), get_y(position), get_width(dimension), border_width, color);
    MLV_draw_filled_rectangle(get_x(position), get_y(position), border_width, get_height(dimension), color);
    MLV_draw_filled_rectangle(get_x(position) + get_width(dimension) - border_width, get_y(position), border_width, get_height(dimension), color);
    MLV_draw_filled_rectangle(get_x(position), get_y(position) + get_height(dimension) - border_width, get_width(dimension), border_width, color);
}

void draw_cross(Position position, Dimension dimension, int border_width, MLV_Color color)
{
    int i;

    int x1 = get_x(position);
    int y1 = get_y(position);

    int x2 = x1 + get_width(dimension);
    int y2 = y1 + get_height(dimension);

    /** Draw horizontal line with the specified border width */
    for (i = -border_width / 2; i <= border_width / 2; i++)
    {
        MLV_draw_line(x1, y1 + i, x2, y2 + i, color);
    }

    /** Draw vertical line with the specified border width */
    for (i = -border_width / 2; i <= border_width / 2; i++)
    {
        MLV_draw_line(x2 + i, y1, x1 + i, y2, color);
    }
}

void draw_rectangle_outline(Position position, Dimension dimension, int border_width, MLV_Color color)
{
    MLV_draw_rectangle(get_x(position), get_y(position), get_width(dimension), get_height(dimension), color);
    draw_border(position, dimension, border_width, color);
}

void draw_filled_rectangle(Position position, Dimension dimension, int border_width, MLV_Color border_width_color, MLV_Color color)
{
    MLV_draw_filled_rectangle(get_x(position), get_y(position), get_width(dimension), get_height(dimension), color);
    draw_border(position, dimension, border_width, border_width_color);
}

void draw_filled_rectangle_with_padding(Position position, Dimension dimension, int border_width, MLV_Color border_width_color, MLV_Color color, int padding)
{
    MLV_draw_filled_rectangle(get_x(position) - padding, get_y(position) - padding, get_width(dimension) + 2 * padding, get_height(dimension) + 2 * padding, color);
    draw_border(position, dimension, border_width, border_width_color);
}

void draw_rounded_filled_rectangle_with_padding(Position position, Dimension dimension, int corner_radius, MLV_Color color, int padding)
{
    /** Draw the main filled rectangle */
    MLV_draw_filled_rectangle(get_x(position) + corner_radius - padding, get_y(position) - padding, get_width(dimension) - 2 * corner_radius + 2 * padding, get_height(dimension) + 2 * padding, color);
    MLV_draw_filled_rectangle(get_x(position) - padding, get_y(position) + corner_radius - padding, get_width(dimension) + 2 * padding, get_height(dimension) - 2 * corner_radius + 2 * padding, color);

    /** Draw the rounded corners */
    MLV_draw_filled_circle(get_x(position) + corner_radius - padding, get_y(position) + corner_radius - padding, corner_radius, color);
    MLV_draw_filled_circle(get_x(position) + get_width(dimension) - corner_radius + padding, get_y(position) + corner_radius - padding, corner_radius, color);
    MLV_draw_filled_circle(get_x(position) + corner_radius - padding, get_y(position) + get_height(dimension) - corner_radius + padding, corner_radius, color);
    MLV_draw_filled_circle(get_x(position) + get_width(dimension) - corner_radius + padding, get_y(position) + get_height(dimension) - corner_radius + padding, corner_radius, color);
}

void draw_filled_circle_with_padding(Position position, int radius, MLV_Color color)
{
    MLV_draw_filled_circle(get_x(position) + radius / 2, get_y(position) + radius / 2, radius, color);
}