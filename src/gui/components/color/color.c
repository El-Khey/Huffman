#include "color.h"

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

void print_color(Color c)
{
    printf("color : { r: %f, g: %f, b: %f, opacity: %f }\n", c.red, c.green, c.blue, c.opacity);
}