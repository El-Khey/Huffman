#ifndef _CHECKBOX_H
#define _CHECKBOX_H

#include "../shape/rectangle/rectangle.h"
#include "../button/button.h"

typedef struct
{
    int is_checked;
    Button button;

    Color checked_color;
    Color default_color;
} Checkbox;

/**
 * @brief Construit une case à cocher.
 *
 * @param position - La position de la case à cocher.
 * @param dimension - La dimension de la case à cocher.
 * @param border_width - La largeur de la bordure de la case à cocher.
 * @param default_color - La couleur par défaut de la case à cocher.
 * @param border_color - La couleur de la bordure de la case à cocher.
 * @param checked_color - La couleur de la case à cocher cochée.
 * @return Checkbox
 */
Checkbox construct_checkbox(Position position, Dimension dimension, int border_width, Color default_color, Color border_color, Color checked_color);

/**
 * @brief Coche ou décoche une case à cocher.
 *
 * @param checkbox - La case à cocher.
 */
void check(Checkbox *checkbox);

/**
 * @brief Dessine une case à cocher.
 *
 * @param checkbox - La case à cocher.
 */
void draw_checkbox(Checkbox checkbox);

#endif