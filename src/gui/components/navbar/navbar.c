#include "navbar.h"

NavBar construct_navbar(Position position, Dimension dimension)
{
    NavBar navbar;

    navbar.rectangle = construct_rectangle(position, dimension, 0, TERTIARY_COLOR, TRANSPARENT_COLOR);
    add_border_to_rectangle(&navbar.rectangle, BORDER_BOTTOM, 2, SECONDARY_COLOR);

    Position button_position = construct_position(get_x(position), get_y(position));
    Dimension button_dimension = construct_dimension(get_width(dimension) / 6, get_height(dimension) - 20);

    navbar.compression_button = construct_button(button_position, button_dimension, 0, construct_color(0.0, 1.0, 0.5, 1.0), TRANSPARENT_COLOR);
    Paddings paddings = construct_paddings(0, 0, 0, 10);
    layout_manager(EAST, &navbar.rectangle, &navbar.compression_button.rectangle, paddings);
    add_button_text(&navbar.compression_button,
                    construct_text("Compress",
                                   position,
                                   "assets/fonts/Roboto/Roboto-Black.ttf",
                                   20,
                                   SECONDARY_COLOR),
                    CENTER);

    return navbar;
}

void draw_navbar(NavBar navbar)
{
    draw_filled_rectangle(navbar.rectangle);
    draw_button(navbar.compression_button);
}