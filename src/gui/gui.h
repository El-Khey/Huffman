#ifndef _GUI_H
#define _GUI_H

#include <stdio.h>
#include <stdlib.h>

#include "manager/gui_manager/gui_manager.h"

/**
 * @brief launch the graphical interface
 */
void launch_graphical_interface();

/**
 * @brief Construct the graphical interface
 *
 * @return GraphicalInterface
 */
GraphicalInterface construct_graphical_interface();

/**
 * @brief Update the graphical interface
 *
 * @param graphical_interface - The graphical interface to update
 */
void update_graphical_interface(GraphicalInterface *graphical_interface);

/**
 * @brief Draw the graphical interface
 *
 * @param graphical_interface - The graphical interface to draw
 */
void draw_graphical_interface(GraphicalInterface graphical_interface);

#endif /** _GUI_H */
