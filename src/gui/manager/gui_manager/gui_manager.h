#ifndef _GUI_MANAGER_H_
#define _GUI_MANAGER_H_

#include <stdio.h>
#include <stdlib.h>

#include "../../../huffman/codec/decompression/decompression.h"
#include "../../../huffman/codec/compression/compression.h"
#include "../../manager/mouse_manager/mouse_manager.h"
#include "../../manager/explorer/explorer.h"
#include "../../components/window/window.h"
#include "../../components/topbar/topbar.h"
#include "../../components/navbar/navbar.h"
#include "../../components/footer/footer.h"
#include "../../components/table/table.h"

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
 * @brief Construct the graphical interface
 *
 * @return GraphicalInterface
 */
void manage_gui_event(GraphicalInterface *graphical_interface);

void update_table_rows(GraphicalInterface *graphical_interface, int direction);

void handle_scroll_bar_event(GraphicalInterface *graphical_interface);

void handle_navbar_back_event(GraphicalInterface *graphical_interface);

void handle_deselect_all_event(GraphicalInterface *graphical_interface);

void handle_delete_event(GraphicalInterface *graphical_interface);

void handle_compress_event(GraphicalInterface *graphical_interface);

void handle_rows_button_event(GraphicalInterface *graphical_interface);

#endif