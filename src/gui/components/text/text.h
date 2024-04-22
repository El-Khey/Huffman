#ifndef TEXT_H
#define TEXT_H

#include "../../utils/dimension/dimension.h"
#include "../../utils/position/position.h"
#include "../shape/rectangle/rectangle.h"
#include "../color/color.h"

#include <string.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>

/**
 * @struct Text
 * @brief Représente un texte avec ses propriétés telles que le contenu, la dimension, la position, la couleur, la police et la taille de la police.
 */
typedef struct
{
    char *text;          /**< Le contenu du texte */
    Rectangle rectangle; /**< Le rectangle du texte */

    Color color;    /**< La couleur du texte */
    MLV_Font *font; /**< La police du texte */

    int font_size;   /**< La taille de la police du texte */
    char *font_path; /**< Le chemin de la police du texte */
} Text;

/**
 * @brief Construit un objet Texte
 *
 * @param text Le texte à construire
 * @param position La position du texte
 * @param font_path Le chemin de la police de caractères
 * @param font_size La taille de la police de caractères
 * @param color La couleur du texte
 * @return Texte
 */
Text construct_text(char *text, Position position, char *font_path, int font_size, Color color);

/**
 * @brief Définit le contenu du texte
 *
 * @param text Le texte dont on veut définir le contenu
 * @param content Le contenu à définir
 */
void set_text_content(Text *text, char *content);

/**
 * @brief Définit la position du texte
 *
 * @param text Le texte dont on veut définir la position
 * @param position La position à définir
 */
void set_text_position(Text *text, Position position);

/**
 * @brief Obtient la largeur du texte
 *
 * @param text Le texte dont on veut obtenir la largeur
 * @return int
 */
int get_text_width(Text text);

/**
 * @brief Obtient la hauteur du texte
 *
 * @param text Le texte dont on veut obtenir la hauteur
 * @return int
 */
int get_text_height(Text text);

/**
 * @brief Dessine un texte
 *
 * @param text Le texte à dessiner
 */
void draw_text(Text text);

/**
 * @brief Dessine un texte avec une ombre
 *
 * @param text Le texte à dessiner
 * @param shadow_offset Le décalage de l'ombre
 */
void draw_text_with_shadow(Text text, int shadow_offset);

/**
 * @brief Détruit un texte
 *
 * @param text Le texte à détruire
 */
void free_text(Text *text);

#endif /** TEXT_H */