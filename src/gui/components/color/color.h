#ifndef _COLOR_H
#define _COLOR_H

#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief structur of the color
 * The color is defined by the red, green, blue and opacity
 * The red, green and blue are between 0 and 1
 * The opacity is between 0 and 1
 */
typedef struct
{
    double red;
    double green;
    double blue;
    double opacity;
} Color;

/**
 * @brief construct a color
 *
 * @param r red
 * @param g green
 * @param b blue
 * @param opacity opacity
 * @return Color
 */
Color construct_color(double r, double g, double b, double opacity);

/**
 * @brief set the color
 *
 * @param color color
 * @param r red
 * @param g green
 * @param b blue
 * @param opacity opacity
 */
void set_color(Color *color, double r, double g, double b, double opacity);

/**
 * @brief convert the color
 *
 * @param c color
 * @return MLV_Color
 */
MLV_Color convert_color(Color c);

/**
 * @brief print the color
 *
 * @param c color
 */
void print_color(Color c);

#endif