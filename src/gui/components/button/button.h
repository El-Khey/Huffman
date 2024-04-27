#ifndef BUTTON_H
#define BUTTON_H

#include "../../manager/layout_manager/layout_manager.h"
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
    BUTTON_TEXT,
    BUTTON_NONE
} ButtonType;

typedef struct
{
    ButtonType type;     /** Le type du bouton */
    Rectangle rectangle; /** Le rectangle du bouton */
    Image image;         /** L'image du bouton */
    Text text;           /** Le texte du bouton */
} Button;

/**
 * @brief C
 *
 * @param position
 * @param dimension
 * @param border_width
 * @param background
 * @param border_color
 * @return Button
 */
Button construct_button(Position position, Dimension dimension, int border_width, Color background, Color border_color);

/**
 * @brief Ajoute un texte à un bouton.
 *
 * @param button
 * @param text
 * @param layout_type
 */
void add_button_text(Button *button, Text text, LayoutType layout_type);

/**
 * @brief Ajoute une image à un bouton.
 *
 * @param button
 * @param image
 * @param layout_type
 */
void add_button_image(Button *button, Image image, LayoutType layout_type);

/**
 * @brief Vérifie si le bouton est survolé.
 *
 * @param button
 * @param p
 * @return int
 */
int is_button_hovered(Button button, Position p);

/**
 * @brief Vérifie si le bouton est cliqué.
 *
 * @param button
 * @param mouse_manager
 * @return int
 */
int is_button_clicked(Button button, MouseManager mouse_manager);

/**
 * @brief Définit la position du bouton.
 *
 * @param button
 * @param position
 */
void set_button_position(Button *button, Position position);

/**
 * @brief Définit la dimension du bouton.
 *
 * @param button
 * @param dimension
 */
void set_button_dimension(Button *button, Dimension dimension);

/**
 * @brief Dessine le bouton.
 *
 * @param button
 */
void draw_button(Button button);

#endif