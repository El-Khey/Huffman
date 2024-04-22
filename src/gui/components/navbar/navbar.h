#ifndef _NAV_BAR_H
#define _NAV_BAR_H

#include "../button/button.h"
#include "../color/theme.h"

typedef struct
{
    Button compression_button;
    Button decompression_button;
    Button help_button;
    Button exit_button;

    Rectangle rectangle;
} NavBar;

/**
 * @brief Construct a NavBar object
 *
 * @param position the position of the NavBar
 * @param dimension the dimension of the NavBar
 * @return NavBar
 */
NavBar construct_navbar(Position position, Dimension dimension);

/**
 * @brief Draw the NavBar
 *
 * @param NavBar the NavBar to draw
 * @return void
 */
void draw_navbar(NavBar navbar);

#endif