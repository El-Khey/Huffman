#ifndef MOUSE_MANAGER_H
#define MOUSE_MANAGER_H

#include "../../utils/position/position.h"
#include <MLV/MLV_all.h>

/**
 * @brief Structure représentant un événement de souris.
 */
typedef struct
{
    int click_count;             /** Le nombre de clics effectués. */
    int is_right_click;          /** Indique si le clic est un clic droit. */
    int is_left_click;           /** Indique si le clic est un clic gauche. */
    int was_right_click_pressed; /** Indique si le bouton droit de la souris était enfoncé. */
    int was_left_click_pressed;  /** Indique si le bouton gauche de la souris était enfoncé. */
} MouseEvent;

/**
 * @brief Structure représentant l'état de la souris.
 */
typedef struct
{
    int right_click; /** Nombre de clics droit effectués. */
    int left_click;  /** Nombre de clics gauche effectués. */
} MouseState;

/**
 * @brief Structure représentant le gestionnaire de souris.
 */
typedef struct
{
    Position position;           /** La position de la souris. */
    MouseState mouse_state;      /** L'état actuel de la souris. */
    MouseState last_mouse_state; /** L'état précédent de la souris. */
    MouseEvent mouse_event;      /** L'événement de la souris. */
    int wheel;                   /** La molette de la souris. */
    int previous_wheel;          /** La molette précédente de la souris. */
} MouseManager;
/**
 * @brief Construit un nouvel objet Mouse Manager avec des valeurs par défaut
 *
 * @return MouseManager
 */
MouseManager construct_mouse_manager();

/**
 * @brief Gère les événements de la souris et met à jour l'état de la souris en conséquence
 *
 * @param mouse_manager L'objet Mouse Manager
 */
void handle_mouse_events(MouseManager *mouse_manager);

/**
 * @brief Vérifie si le bouton droit de la souris est cliqué
 * Un clic est défini comme une pression et un relâchement du bouton
 *
 * @param mouse_manager L'objet Mouse Manager
 * @return int
 */
int is_right_button_clicked(MouseManager mouse_manager);

/**
 * @brief Vérifie si le bouton gauche de la souris est cliqué
 * Un clic est défini comme une pression et un relâchement du bouton
 *
 * @param mouse_manager L'objet Mouse Manager
 * @return int
 */
int is_left_button_clicked(MouseManager mouse_manager);

/**
 * @brief Définit l'état relâché de la souris
 *
 * @param mouse_manager L'objet Mouse Manager
 */
void set_mouse_released(MouseManager *mouse_manager);

/**
 * @brief Obtient la position de la souris
 *
 * @param mouse_manager L'objet Mouse Manager
 * @return Position
 */
Position get_mouse_position(MouseManager mouse_manager);

/**
 * @brief Vérifie si la molette de la souris a été déplacée
 *
 * @param mouse_manager L'objet Mouse Manager
 * @return int
 */
int is_wheel_scrolled(MouseManager mouse_manager);

/**
 * @brief Gère les événements de la molette de la souris
 *
 * @param mouse_manager L'objet Mouse Manager
 */
void handle_mouse_wheel_event(MouseManager *mouse_manager);

#endif