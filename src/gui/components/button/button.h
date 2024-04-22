#ifndef BUTTON_H
#define BUTTON_H

#include "../../manager/mouse_manager/mouse_manager.h"

#include "../../utils/dimension/dimension.h"
#include "../../utils/position/position.h"
#include "../shape/rectangle/rectangle.h"
#include "../image/image.h"
#include "../text/text.h"

/**
 * @struct Button
 * @brief Représente un bouton dans l'interface graphique.
 *
 * Cette structure contient les informations nécessaires pour afficher et gérer un bouton.
 * Elle inclut une image, une animation, une position, une dimension, un texte, ainsi que les couleurs de fond et de premier plan.
 */

typedef enum
{
    BUTTON_IMAGE,
    BUTTON_TEXT
} ButtonType;

typedef struct
{
    ButtonType type;     /** Le type du bouton */
    Rectangle rectangle; /** Le rectangle du bouton */
    Image image;         /** L'image du bouton */
    Text text;           /** Le texte du bouton */
} Button;

Button construct_button(Position position, Dimension dimension, int border_width, Color background, Color border_color);

/**
 * @brief Construit un nouvel objet Button avec une image
 *
 * @param image L'image du bouton
 * @param position La position du bouton
 * @param dimension La dimension du bouton
 * @return Button
 */
Button construct_button_with_image(Image image, Position position, Dimension dimension);

/**
 * @brief Construit un nouvel objet Button avec un texte
 *
 * @param text Le texte du bouton
 * @param position La position du bouton
 * @param dimension La dimension du bouton
 * @return Button
 */
Button construct_button_with_text(char *text, Position position, Dimension dimension, MLV_Color foreground, MLV_Color background);

/**
 * @brief Définit la position du bouton
 *
 * @param button Le bouton dont on veut définir la position
 * @param position La position à définir pour le bouton
 */
void set_button_position(Button *button, Position position);

/**
 * @brief Définit la dimension du bouton
 *
 * @param button Le bouton dont on veut définir la dimension
 * @param dimension La dimension à définir pour le bouton
 */
void set_button_dimension(Button *button, Dimension dimension);

/**
 * @brief Dessine le bouton avec un effet de survol
 *
 * @param button Le bouton à dessiner
 * @param mouse_position La position de la souris
 * @param border_color La couleur de la bordure
 * @param background La couleur de fond
 */
void draw_filled_button_with_hover_effect(Button button, Position mouse_position, MLV_Color border_color, MLV_Color background);

/**
 * @brief Dessine le bouton survolé
 *
 * @param button Le bouton à dessiner
 * @param mouse_position La position de la souris
 * @param border_color La couleur de la bordure
 * @param background La couleur de fond
 */
void draw_hovered_button(Button button, Position mouse_position, MLV_Color border_color, MLV_Color background);

/**
 * @brief Vérifie si le bouton est survolé
 *
 * @param button Le bouton à vérifier s'il est survolé
 * @param p La position à vérifier si le bouton est survolé
 * @return int
 */
int is_button_hovered(Button button, Position p);

/**
 * @brief Vérifie si le bouton est cliqué
 *
 * @param button Le bouton à vérifier s'il est cliqué
 * @param mouse_manager Le gestionnaire de souris pour vérifier si le bouton est cliqué
 * @return int
 */
int is_button_clicked(Button button, MouseManager mouse_manager);

/**
 * @brief Dessine l'image du bouton
 *
 * @param button Le bouton à dessiner
 */
void draw_button_image(Button button);

/**
 * @brief Dessine le texte du bouton
 *
 * @param button Le bouton dont on veut dessiner le texte
 */
void draw_button_text(Button button);

/**
 * @brief Libère l'image du bouton
 *
 * @param button Le bouton dont on veut libérer l'image
 */
void free_button_image(Button *button);

/**
 * @brief Libère le texte du bouton
 *
 * @param button Le bouton dont on veut libérer le texte
 */
void free_button_text(Button *button);

#endif