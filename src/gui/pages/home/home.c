#include "home.h"

static void initialize_table(HomePage *home_page);

HomePage construct_home_page()
{
    HomePage home_page;

    home_page.window = construct_window();

    home_page.topbar = construct_topbar(construct_position(0, 0), construct_dimension(TOP_BAR_WIDTH, TOP_BAR_HEIGHT));
    home_page.navbar = construct_navbar(construct_position(0, TOP_BAR_HEIGHT), construct_dimension(NAV_BAR_WIDTH, NAV_BAR_HEIGHT));

    home_page.mouse_manager = construct_mouse_manager();
    home_page.explorer = construct_explorer(".");

    explore(&home_page.explorer, ".");
    order_directories(&home_page.explorer.directories);
    order_files(&home_page.explorer.files);

    initialize_table(&home_page);
    return home_page;
}

static void initialize_table(HomePage *home_page)
{
    char *absolute_path = get_absolute_path(home_page->explorer.current_directory.path);
    update_navbar_text(&home_page->navbar, absolute_path);

    home_page->table = construct_table(construct_position(0, TOP_BAR_HEIGHT + NAV_BAR_HEIGHT),
                                       construct_dimension(WINDOW_WIDTH, WINDOW_HEIGHT - TOP_BAR_HEIGHT - NAV_BAR_HEIGHT),
                                       10, 6, TRANSPARENT_COLOR, LIGHT_COLOR);
    add_column(&home_page->table, construct_position(25, get_y(home_page->table.rectangle.position)), construct_dimension(100, 50), "");
    add_column(&home_page->table, construct_position(50, get_y(home_page->table.rectangle.position)), construct_dimension(50, 50), "");
    add_column(&home_page->table, construct_position(125, get_y(home_page->table.rectangle.position)), construct_dimension(150, 50), "Name");
    add_column(&home_page->table, construct_position(400, get_y(home_page->table.rectangle.position)), construct_dimension(50, 50), "Size");
    add_column(&home_page->table, construct_position(550, get_y(home_page->table.rectangle.position)), construct_dimension(100, 50), "Type");
    add_column(&home_page->table, construct_position(800, get_y(home_page->table.rectangle.position)), construct_dimension(100, 50), "Last Modified");

    for (int i = 0; i < home_page->explorer.directories.number_of_directories; i++)
    {
        add_row(&home_page->table, home_page->explorer.directories.list[i].path, home_page->explorer.directories.list[i].name, home_page->explorer.directories.list[i].metadata.size, home_page->explorer.directories.list[i].metadata.type, home_page->explorer.directories.list[i].metadata.last_modified);
    }

    for (int i = 0; i < home_page->explorer.files.number_of_files; i++)
    {
        add_row(&home_page->table, home_page->explorer.files.list[i].path, home_page->explorer.files.list[i].name, home_page->explorer.files.list[i].metadata.size, home_page->explorer.files.list[i].metadata.type, home_page->explorer.files.list[i].metadata.last_modified);
    }
}

void update_home_page(HomePage *home_page)
{
    handle_mouse_events(&home_page->mouse_manager);
    handle_table_selection(&home_page->table, home_page->mouse_manager);
}

void draw_home_page(HomePage home_page)
{
    draw_window(home_page.window);
    draw_topbar(home_page.topbar);
    draw_navbar(home_page.navbar);
    draw_table(home_page.table);
}
