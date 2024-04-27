#include "color.h"

Color PRIMARY_COLOR;
Color SECONDARY_COLOR;

Color SPECIAL_COLOR;
Color TEXT_COLOR;

Color construct_color(double r, double g, double b, double opacity)
{
    Color c;

    c.blue = b;
    c.green = g;
    c.red = r;

    c.opacity = opacity;

    return c;
}

void set_color(Color *color, double r, double g, double b, double opacity)
{
    color->red = r;
    color->green = g;
    color->blue = b;
    color->opacity = opacity;
}

MLV_Color convert_color(Color c)
{
    return MLV_rgba(c.red * 255, c.green * 255, c.blue * 255, c.opacity * 255);
}

void light_theme()
{
    PRIMARY_COLOR = construct_color(1.0, 1.0, 1.0, 1.0);
    SECONDARY_COLOR = construct_color(0.0, 0.0, 0.0, 1.0);
    SPECIAL_COLOR = construct_color(0.42, 0.22, 1.0, 1.0);
    TEXT_COLOR = construct_color(0.0, 0.0, 0.0, 1.0);
}

void dark_theme()
{
    PRIMARY_COLOR = construct_color(0.149, 0.149, 0.149, 1.0);
    SECONDARY_COLOR = construct_color(0.956, 0.956, 0.956, 1.0);
    SPECIAL_COLOR = construct_color(0.22, 0.42, 1.0, 1.0);
    TEXT_COLOR = construct_color(0.956, 0.956, 0.956, 1.0);
}

int is_dark_theme()
{
    return PRIMARY_COLOR.red == 0.149 && PRIMARY_COLOR.green == 0.149 && PRIMARY_COLOR.blue == 0.149;
}

void print_color(Color c)
{
    printf("color : { r: %f, g: %f, b: %f, opacity: %f }\n", c.red, c.green, c.blue, c.opacity);
}
