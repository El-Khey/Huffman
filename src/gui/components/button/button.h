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

void add_button_text(Button *button, Text text, LayoutType layout_type);

void add_button_image(Button *button, char *image_path);

int is_button_hovered(Button button, Position p);

void set_button_position(Button *button, Position position);

void set_button_dimension(Button *button, Dimension dimension);

void draw_button(Button button);

#endif