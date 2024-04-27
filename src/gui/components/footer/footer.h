#ifndef _FOOTER_H
#define _FOOTER_H

#include <stdio.h>
#include <stdlib.h>

#include "../../manager/layout_manager/layout_manager.h"
#include "../shape/rectangle/rectangle.h"
#include "../button/button.h"
#include "../color/theme.h"
#include "../text/text.h"

#define FOOTER_HEIGHT 50

typedef struct
{
    Rectangle rectangle;
    Text text;

    Button theme_button;
} Footer;

/**
 * @brief construct a Footer object
 *
 * @param position - The position of the footer
 * @param dimension - The dimension of the footer
 * @param text - The text of the footer
 * @return Footer
 */
Footer construct_footer(Position position, Dimension dimension, char *text);

/**
 * @brief format the text of the footer
 *
 * @param number_of_selected_elements - The number of selected elements
 * @param total_size - The total size of the selected elements
 * @return char*
 */
char *format_footer_text(int number_of_selected_elements, long total_size);

/**
 * @brief update the text of the footer
 *
 * @param footer - The footer to update
 * @param text - The text to update
 */
void update_footer_text(Footer *footer, char *text);

/**
 * @brief draw the footer
 *
 * @param footer - The footer to draw
 */
void draw_footer(Footer footer);

#endif /** _FOOTER_H */