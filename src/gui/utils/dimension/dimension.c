#include "dimension.h"

Dimension construct_dimension(int width, int height)
{
    Dimension dimension;

    dimension.width = width;
    dimension.height = height;

    return dimension;
}

void resize_dimension(Dimension *dimension, int width, int height)
{
    set_width(dimension, width);
    set_height(dimension, height);
}

int get_width(Dimension dimension)
{
    return dimension.width;
}

int get_height(Dimension dimension)
{
    return dimension.height;
}

void set_width(Dimension *dimension, int width)
{
    dimension->width = width;
}

void set_height(Dimension *dimension, int height)
{
    dimension->height = height;
}

Dimension scale_down_dimension(Dimension dimension, int factor)
{
    return construct_dimension(get_width(dimension) / factor, get_height(dimension) / factor);
}

void print_dimension(Dimension dimension)
{
    printf("Dimension: %dx%d\n", dimension.width, dimension.height);
}