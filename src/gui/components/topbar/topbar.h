#ifndef _TOP_BAR_H
#define _TOP_BAR_H

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
} TopBar;

/**
 * @brief Construct a TopBar object
 *
 * @param position the position of the TopBar
 * @param dimension the dimension of the TopBar
 * @return TopBar
 */
TopBar construct_topbar(Position position, Dimension dimension);

/**
 * @brief Draw the TopBar
 *
 * @param TopBar the TopBar to draw
 * @return void
 */
void draw_topbar(TopBar topbar);

#endif