#ifndef _NAV_BAR_H
#define _NAV_BAR_H

#include "../button/button.h"
#include "../window/window.h"
#include "../color/theme.h"

#define NAV_BAR_WIDTH WINDOW_WIDTH
#define NAV_BAR_HEIGHT 35

typedef struct
{
    Rectangle background;
    Text displayed_path;
    Button back;
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
 * @brief Update the NavBar text
 *
 * @param navbar the NavBar to update
 * @param absolute_path the absolute path to set
 * @return void
 */
void update_navbar_text(NavBar *navbar, char *absolute_path);

/**
 * @brief Draw the NavBar
 *
 * @param NavBar the NavBar to draw
 * @return void
 */
void draw_navbar(NavBar navbar);

#endif /** _NAV_BAR_H */