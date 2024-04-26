#ifndef _GUI_H
#define _GUI_H

#include <stdio.h>
#include <stdlib.h>

#include "../huffman/codec/decompression/decompression.h"
#include "../huffman/codec/compression/compression.h"
#include "manager/mouse_manager/mouse_manager.h"
#include "manager/explorer/explorer.h"
#include "components/window/window.h"
#include "components/topbar/topbar.h"
#include "components/navbar/navbar.h"
#include "components/footer/footer.h"
#include "components/table/table.h"

typedef struct
{
    MouseManager mouse_manager;
    Window window;
    TopBar topbar;
    NavBar navbar;
    Explorer explorer;
    Table table;
    Footer footer;
} GraphicalInterface;

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
