#include "gui.h"

GraphicalInterface construct_graphical_interface()
{
    GraphicalInterface graphical_interface;
    char *absolute_path = get_absolute_path(".");

    graphical_interface.window = construct_window();
    graphical_interface.topbar = construct_topbar(construct_position(0, 0), construct_dimension(TOP_BAR_WIDTH, TOP_BAR_HEIGHT));
    graphical_interface.navbar = construct_navbar(construct_position(0, TOP_BAR_HEIGHT), construct_dimension(NAV_BAR_WIDTH, NAV_BAR_HEIGHT));

    graphical_interface.mouse_manager = construct_mouse_manager();
    graphical_interface.explorer = construct_explorer();

    explore(&graphical_interface.explorer, absolute_path);
    update_navbar_text(&graphical_interface.navbar, absolute_path);

    order_explorer(&graphical_interface.explorer);
    graphical_interface.table = construct_table(construct_position(0, TOP_BAR_HEIGHT + NAV_BAR_HEIGHT),
                                                construct_dimension(WINDOW_WIDTH, WINDOW_HEIGHT - TOP_BAR_HEIGHT - NAV_BAR_HEIGHT),
                                                10, 6, TRANSPARENT_COLOR, LIGHT_COLOR);
    add_column(&graphical_interface.table, construct_position(25, get_y(graphical_interface.table.rectangle.position)), construct_dimension(100, 50), "");
    add_column(&graphical_interface.table, construct_position(50, get_y(graphical_interface.table.rectangle.position)), construct_dimension(50, 50), "");
    add_column(&graphical_interface.table, construct_position(125, get_y(graphical_interface.table.rectangle.position)), construct_dimension(150, 50), "Name");
    add_column(&graphical_interface.table, construct_position(400, get_y(graphical_interface.table.rectangle.position)), construct_dimension(50, 50), "Size");
    add_column(&graphical_interface.table, construct_position(550, get_y(graphical_interface.table.rectangle.position)), construct_dimension(100, 50), "Type");
    add_column(&graphical_interface.table, construct_position(800, get_y(graphical_interface.table.rectangle.position)), construct_dimension(100, 50), "Last Modified");
    update_table_rows(&graphical_interface, graphical_interface.mouse_manager.wheel);

    graphical_interface.footer = construct_footer(construct_position(0, WINDOW_HEIGHT - FOOTER_HEIGHT),
                                                  construct_dimension(WINDOW_WIDTH, FOOTER_HEIGHT),
                                                  "0 Elements selected - Total Size 0 byte ");
    return graphical_interface;
}

void launch_graphical_interface()
{
    GraphicalInterface graphical_interface = construct_graphical_interface();
    while (1)
    {
        update_graphical_interface(&graphical_interface);
        draw_graphical_interface(graphical_interface);
    }
}

void update_graphical_interface(GraphicalInterface *graphical_interface)
{
    handle_mouse_events(&graphical_interface->mouse_manager);
    handle_table_selection(&graphical_interface->table, graphical_interface->mouse_manager);
    update_footer_text(&graphical_interface->footer, format_footer_text(graphical_interface->table.rows_to_compress.number_saved_files, graphical_interface->table.rows_to_compress.total_size));

    manage_gui_event(graphical_interface);
}

void draw_graphical_interface(GraphicalInterface graphical_interface)
{
    draw_window(graphical_interface.window);
    draw_topbar(graphical_interface.topbar);
    draw_navbar(graphical_interface.navbar);
    draw_table(graphical_interface.table);
    draw_footer(graphical_interface.footer);
}
