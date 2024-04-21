#ifndef _COLOR_H
#define _COLOR_H

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief structur of the color
 *
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
 * @brief print the color
 *
 * @param c color
 */
void print_color(Color c);

#endif