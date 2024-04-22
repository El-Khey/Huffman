#ifndef _CROSS_H
#define _CROSS_H

#include "../shape.h"

typedef struct
{
    Position position;
    Dimension dimension;
    Color color;

    int width;
} Cross;

/**
 * @brief construct a cross
 *
 * @param position position
 * @param dimension dimension
 * @param color color
 * @param width border width
 * @return Cross
 */
Cross construct_cross(Position position, Dimension dimension, Color color, int border_width);

/**
 * @brief draw a cross
 *
 * @param cross cross
 * @return void
 */
void draw_cross(Cross cross);

#endif