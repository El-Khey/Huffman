#ifndef _TABLE_H
#define _TABLE_H

#include "../../manager/layout_manager/layout_manager.h"
#include "../checkbox/checkbox.h"
#include "../button/button.h"
#include "../image/image.h"
#include "../color/theme.h"
#include "../text/text.h"

typedef struct
{
    Rectangle rectangle;
    Button button;

    Checkbox checkbox;
    Image icon;

    Text filename;
    Text size;

    Text type;
    Text last_modified;

    char *path;
} Row;

typedef struct
{
    Rectangle rectangle;
    Text text;
} Column;

typedef struct
{
    Rectangle rectangle;
    int scroll_index;

    int max_rows;
    Row *rows;
    int row_index;

    int number_columns;
    Column *columns;
    int column_index;

    Color background_color;
    Color text_color;
} Table;

/**
 * @brief Construit un tableau.
 *
 * @param position - La position du tableau.
 * @param dimension - La dimension du tableau.
 * @param max_rows - Le nombre de lignes du tableau.
 * @param number_columns - Le nombre de colonnes du tableau.
 * @param bacground_color - La couleur de fond du tableau.
 * @param text_color - La couleur du texte du tableau.
 * @return Table
 */
Table construct_table(Position position, Dimension dimension, int max_rows, int number_columns, Color bacground_color, Color text_color);

/**
 * @brief Ajoute une colonne au tableau.
 *
 * @param table - Le tableau.
 * @param position - La position de la colonne.
 * @param dimension - La dimension de la colonne.
 * @param text - Le texte de la colonne.
 */
void add_column(Table *table, Position position, Dimension dimension, char *text);

/**
 * @brief Ajoute une ligne au tableau.
 *
 * @param table - Le tableau.
 * @param path - Le chemin de la ligne.
 * @param filename - Le nom de fichier de la ligne.
 * @param size - La taille de la ligne.
 * @param type - Le type de la ligne.
 * @param last_modified - La date de dernière modification de la ligne.
 */
void add_row(Table *table, char *path, char *filename, long size, char *type, char *last_modified);

/**
 * @brief Nettoie les lignes du tableau.
 *
 * @param table - Le tableau.
 */
void clear_table_rows(Table *table);

/**
 * @brief Gère la sélection d'une ligne du tableau.
 *
 * @param table - Le tableau.
 * @param mouse_manager - Le gestionnaire de la souris.
 */
void handle_table_selection(Table *table, MouseManager mouse_manager);

/**
 * @brief Dessine un tableau.
 *
 * @param table - Le tableau.
 */
void draw_table(Table table);

#endif
