#ifndef _NAV_BAR_H
#define _NAV_BAR_H

#include "../button/button.h"
#include "../color/theme.h"

typedef enum
{
    COMPRESSION,
    EXTRACTION,
    VIEW,
    DELETE,
    DESELECT,
    number_of_buttons
} NavBarButtonType;

typedef struct
{
    Button buttons[number_of_buttons];
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