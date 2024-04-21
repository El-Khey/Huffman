#ifndef DIMENSION_H
#define DIMENSION_H

#include <stdio.h>

/**
 * @brief Structure représentant les dimensions d'un objet.
 */
typedef struct
{
    int width;  /**< La largeur de l'objet. */
    int height; /**< La hauteur de l'objet. */
} Dimension;

/**
 * @brief Construit un objet Dimension avec la largeur et la hauteur données
 *
 * @param width La largeur de la dimension
 * @param height La hauteur de la dimension
 * @return Dimension
 */
Dimension construct_dimension(int width, int height);

/**
 * @brief Redimensionne la dimension donnée avec la largeur et la hauteur données
 *
 * @param dimension La dimension à redimensionner
 * @param width La largeur pour redimensionner la dimension
 * @param height La hauteur pour redimensionner la dimension
 */
void resize_dimension(Dimension *dimension, int width, int height);

/**
 * @brief Obtient la largeur de la dimension
 *
 * @param dimension La dimension
 * @return int
 */
int get_width(Dimension dimension);

/**
 * @brief Obtient la hauteur de la dimension
 *
 * @param dimension La dimension
 * @return int
 */
int get_height(Dimension dimension);

/**
 * @brief Définit la largeur de la dimension
 *
 * @param dimension La dimension
 * @param width La largeur
 */
void set_width(Dimension *dimension, int width);

/**
 * @brief Définit la hauteur de la dimension
 *
 * @param dimension La dimension
 * @param height La hauteur
 */
void set_height(Dimension *dimension, int height);

/**
 * @brief Réduit la dimension donnée en utilisant le facteur donné
 *
 * @param dimension La dimension
 * @param factor Le facteur de réduction
 * @return Dimension
 */
Dimension scale_down_dimension(Dimension dimension, int factor);

/**
 * @brief Affiche la dimension donnée à l'écran
 * La dimension est affichée dans le format suivant : Dimension: largeurxhauteur
 * Doit être utilisé uniquement à des fins de débogage
 *
 * @param dimension La dimension à afficher
 */
void print_dimension(Dimension dimension);

#endif /** DIMENSION_H */