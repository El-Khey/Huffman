#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "../shape.h"

typedef enum
{
    BORDER_TOP,
    BORDER_RIGHT,
    BORDER_BOTTOM,
    BORDER_LEFT,
    num_borders
} BorderType;

typedef struct
{
    int border_width;
    Color border_color;
    int is_visible;
} Border;

typedef struct
{
    Border borders[num_borders];
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
 * @brief check if a rectangle is hovered
 *
 * @param rectangle rectangle
 * @param p position
 * @return int
 */
int is_rectangle_hovered(Rectangle rectangle, Position p);

/**
 * @brief add a border to a rectangle
 *
 * @param rectangle rectangle
 * @param border_type border type
 * @param border_width border width
 * @param border_color border color
 * @return void
 */
void add_border_to_rectangle(Rectangle *rectangle, BorderType border_type, int border_width, Color border_color);

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

#endif