#ifndef _CHECKBOX_H
#define _CHECKBOX_H

#include "../shape/rectangle/rectangle.h"

typedef struct
{
    int is_checked;
    Rectangle rectangle;

    Color checked_color;
    Color default_color;
} Checkbox;

Checkbox construct_checkbox(Position position, Dimension dimension, int border_width, Color default_color, Color border_color, Color checked_color);

void check(Checkbox checkbox);

void draw_checkbox(Checkbox checkbox);

#endif