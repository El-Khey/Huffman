#include "navbar.h"

NavBar construct_navbar(Position position, Dimension dimension)
{
    NavBar navbar;

    navbar.background = construct_rectangle(position, dimension, 0, LIGHT_COLOR, TRANSPARENT_COLOR);
    navbar.back = construct_button(construct_position(0, 0), construct_dimension(35, 35), 0, TRANSPARENT_COLOR, TRANSPARENT_COLOR);
    layout_manager(EAST, &navbar.background, &navbar.back.rectangle, construct_paddings(0, 0, 0, 20));
    add_button_image(&navbar.back, construct_image("assets/icons/arrow-backward.png", navbar.back.rectangle.position, navbar.back.rectangle.dimension), CENTER);

    navbar.displayed_path = construct_text("",
                                           construct_position(get_x(navbar.back.rectangle.position) + get_width(navbar.back.rectangle.dimension),
                                                              get_y(navbar.back.rectangle.position)),
                                           "assets/fonts/Raleway/static/Raleway-MediumItalic.ttf", 20, DARK_COLOR);

    int border_width = 2;
    set_text_dimensions(&navbar.displayed_path, construct_dimension(NAV_BAR_WIDTH - get_width(navbar.back.rectangle.dimension) - 30, NAV_BAR_HEIGHT - border_width * 4));
    layout_manager(EAST, &navbar.background, &navbar.displayed_path.rectangle, construct_paddings(0, 0, 0, get_width(navbar.back.rectangle.dimension) + 25));

    add_border_to_rectangle(&navbar.displayed_path.rectangle, BORDER_BOTTOM, border_width, BLACK_COLOR);
    add_border_to_rectangle(&navbar.displayed_path.rectangle, BORDER_TOP, border_width, BLACK_COLOR);
    add_border_to_rectangle(&navbar.displayed_path.rectangle, BORDER_LEFT, border_width, BLACK_COLOR);
    add_border_to_rectangle(&navbar.displayed_path.rectangle, BORDER_RIGHT, border_width, BLACK_COLOR);

    return navbar;
}

void draw_navbar(NavBar navbar)
{
    draw_filled_rectangle(navbar.background);
    draw_button(navbar.back);
    draw_text(navbar.displayed_path);
}