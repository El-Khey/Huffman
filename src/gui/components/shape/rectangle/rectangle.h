#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "../shape.h"

typedef struct
{
    Dimension dimension;
    Position position;

    Color background_color;
    Color border_color;

    int border_width;
} Rectangle;

/**
 * @brief construct a rectangle
 *
 * @param position position
 * @param dimension dimension
 * @param color color
 * @return Rectangle
 */
Rectangle construct_rectangle(Position position, Dimension dimension, int border_width, Color background, Color border_color);

/**
 * @brief draw a filled rectangle
 *
 * @param rectangle rectangle
 * @return void
 */
void draw_filled_rectangle(Rectangle rectangle);

/**
 * @brief draw a rectangle outline
 *
 * @param rectangle rectangle
 * @return void
 */
void draw_rectangle_outline(Rectangle rectangle);

/**
 * @brief draw a filled rectangle with border
 *
 * @param rectangle rectangle
 * @return void
 */
void draw_filled_rectangle_with_border(Rectangle rectangle);

#endif