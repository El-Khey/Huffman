#include "home.h"

HomePage construct_home_page()
{
    HomePage home_page;

    home_page.window = construct_window();
    home_page.topbar = construct_topbar(construct_position(0, 0), construct_dimension(WINDOW_WIDTH, 110));

    home_page.mouse_manager = construct_mouse_manager();
    return home_page;
}

void update_home_page(HomePage *home_page)
{
    handle_mouse_events(&home_page->mouse_manager);
    if (is_left_button_clicked(home_page->mouse_manager))
    {
        printf("Left button clicked\n");
        print_position(home_page->mouse_manager.position);
    }
}

void draw_home_page(HomePage home_page)
{
    draw_window(home_page.window);
    draw_topbar(home_page.topbar);
}
