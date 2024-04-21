#ifndef Position_H
#define Position_H

#include <stdio.h>

/**
 * @struct Position
 * @brief Représente une position avec ses coordonnées x et y.
 */
typedef struct
{
    int x, y;
} Position;

/**
 * @brief Construit un nouvel objet Position avec les coordonnées données
 *
 * @param x La coordonnée x
 * @param y La coordonnée y
 * @return Position
 */
Position construct_position(int x, int y);

/**
 * @brief Obtient la coordonnée x de la position donnée
 *
 * @param p La position
 * @return int
 */
int get_x(Position p);

/**
 * @brief Obtient la coordonnée y de la position donnée
 *
 * @param p La position
 * @return int
 */
int get_y(Position p);

/**
 * @brief Définit la coordonnée x de la position donnée
 *
 * @param p La position
 * @param x La nouvelle coordonnée x
 */
void set_x(Position *p, int x);

/**
 * @brief Définit la coordonnée y de la position donnée
 *
 * @param p La position
 * @param y La nouvelle coordonnée y
 */
void set_y(Position *p, int y);

/**
 * @brief Déplace la position donnée de la quantité donnée dans la direction x
 *
 * @param p La position
 * @param dx La quantité à déplacer dans la direction x
 */
void move_y(Position *p, int dy);

/**
 * @brief Déplace la position donnée de la quantité donnée dans la direction y
 *
 * @param p La position
 * @param dx La quantité à déplacer dans la direction y
 */
void move_x(Position *p, int dx);

/**
 * @brief Déplace la position donnée de la quantité donnée
 *
 * @param p La position
 * @param dx La quantité à déplacer dans la direction x
 * @param dy La quantité à déplacer dans la direction y
 */
void move_position(Position *p, int dx, int dy);

/**
 * @brief Affiche la position donnée à l'écran
 * La position est affichée dans le format suivant : Position : (x, y)
 * Doit être utilisé uniquement à des fins de débogage
 *
 * @param p La position à afficher
 */
void print_position(Position p);

#endif