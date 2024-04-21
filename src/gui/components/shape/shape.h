#ifndef SHAPE_H
#define SHAPE_H

#include <MLV/MLV_all.h>

#include "../../utils/dimension/dimension.h"
#include "../../utils/position/position.h"

/**
 * @brief Structure représentant un rectangle.
 */
typedef struct
{
    Position position;   /**< La position du rectangle. */
    Dimension dimension; /**< Les dimensions du rectangle. */

    MLV_Color color; /**< La couleur du rectangle. */
} Rectangle;

typedef Rectangle Shape; /**< Alias pour le type Rectangle, représentant une forme. */

/**
 * @brief Construit un rectangle avec les paramètres donnés.
 *
 * @param position La position du rectangle.
 * @param dimension Les dimensions du rectangle.
 * @param color La couleur du rectangle.
 * @return Le rectangle construit.
 */
Rectangle construct_rectangle(Position position, Dimension dimension, MLV_Color color);

/**
 * Dessine un rectangle sur l'écran.
 *
 * @param rectangle Le rectangle à dessiner.
 */
void draw_rectangle(Rectangle rectangle);

/**
 * @brief Dessine un rectangle dégradé.
 *
 * @param x1 La position x du premier point.
 * @param y1 La position y du premier point.
 * @param x2 La position x du deuxième point.
 * @param y2 La position y du deuxième point.
 * @param color1 La première couleur.
 * @param color2 La deuxième couleur.
 */
void draw_gradient_rectangle(Position position1, Position position2, MLV_Color color1, MLV_Color color2);

/**
 * @brief Dessine un rectangle dégradé vertical.
 *
 * @param x1 La position x du premier point.
 * @param y1 La position y du premier point.
 * @param x2 La position x du deuxième point.
 * @param y2 La position y du deuxième point.
 * @param color1 La première couleur.
 * @param color2 La deuxième couleur.
 */
void draw_vertical_gradient_rectangle(Position position1, Position position2, MLV_Color color1, MLV_Color color2);

/**
 * @brief Dessine un rectangle arrondi rempli.
 *
 * @param position La position du rectangle.
 * @param dimension La dimension du rectangle.
 * @param corner_radius Le rayon des coins.
 * @param color La couleur du rectangle.
 */
void draw_rounded_filled_rectangle(Position position, Dimension dimension, int corner_radius, MLV_Color color);

/**
 * @brief Dessine une bordure.
 *
 * @param position La position de la bordure.
 * @param dimension La dimension de la bordure.
 * @param border_width La largeur de la bordure.
 * @param color La couleur de la bordure.
 */
void draw_border(Position position, Dimension dimension, int border_width, MLV_Color color);

/**
 * @brief Dessine une croix.
 *
 * @param position La position de la croix.
 * @param dimension La dimension de la croix.
 * @param border_width La largeur de la croix.
 * @param color La couleur de la croix.
 */
void draw_cross(Position position, Dimension dimension, int border_width, MLV_Color color);

/**
 * @brief Dessine un rectangle avec contour.
 *
 * @param position La position du rectangle.
 * @param dimension La dimension du rectangle.
 * @param border_width La largeur du contour.
 * @param color La couleur du rectangle.
 */
void draw_rectangle_outline(Position position, Dimension dimension, int border_width, MLV_Color color);

/**
 * @brief Dessine un rectangle rempli.
 *
 * @param position La position du rectangle.
 * @param dimension La dimension du rectangle.
 * @param border_width La largeur du rectangle.
 * @param border_width_color La couleur du contour du rectangle.
 * @param color La couleur du rectangle.
 */
void draw_filled_rectangle(Position position, Dimension dimension, int border_width, MLV_Color border_width_color, MLV_Color color);

/**
 * @brief Dessine un rectangle rempli avec un padding.
 *
 * @param position La position du rectangle.
 * @param dimension La dimension du rectangle.
 * @param border_width La largeur du rectangle.
 * @param border_width_color La couleur du contour du rectangle.
 * @param color La couleur du rectangle.
 * @param padding Le padding du rectangle.
 */
void draw_filled_rectangle_with_padding(Position position, Dimension dimension, int border_width, MLV_Color border_width_color, MLV_Color color, int padding);

/**
 * @brief Dessine un rectangle arrondi rempli avec un padding.
 *
 * @param position La position du rectangle.
 * @param dimension La dimension du rectangle.
 * @param corner_radius Le rayon des coins.
 * @param color La couleur du rectangle.
 * @param padding Le padding du rectangle.
 */
void draw_rounded_filled_rectangle_with_padding(Position position, Dimension dimension, int corner_radius, MLV_Color color, int padding);

/**
 * @brief Dessine un cercle rempli avec un padding.
 *
 * @param position La position du cercle.
 * @param radius Le rayon du cercle.
 * @param color La couleur du cercle.
 */
void draw_filled_circle_with_padding(Position position, int radius, MLV_Color color);

#endif