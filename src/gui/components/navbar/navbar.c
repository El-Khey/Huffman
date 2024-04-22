#include "navbar.h"

NavBar construct_navbar(Position position, Dimension dimension)
{
    NavBar navbar;

    navbar.rectangle = construct_rectangle(position, dimension, 0, PRIMARY_COLOR, TRANSPARENT_COLOR);
    add_border_to_rectangle(&navbar.rectangle, BORDER_BOTTOM, 5, SECONDARY_COLOR);
    Paddings paddings = construct_paddings(0, 22, 0, 22);

    Dimension button_dimension = construct_dimension(75, 90);

    navbar.buttons[COMPRESSION] = construct_button(construct_position(get_x(position), get_y(position)), button_dimension, 0, PRIMARY_COLOR, TRANSPARENT_COLOR);
    layout_manager(EAST, &navbar.rectangle, &navbar.buttons[COMPRESSION].rectangle, paddings);
    Image compress_icon = construct_image("assets/icons/compress.png", navbar.buttons[COMPRESSION].rectangle.position, button_dimension);
    add_button_image(&navbar.buttons[COMPRESSION], compress_icon, CENTER);

    navbar.buttons[EXTRACTION] = construct_button(
        construct_position(
            get_x(navbar.buttons[COMPRESSION].rectangle.position) + get_width(navbar.buttons[COMPRESSION].rectangle.dimension) + 36,
            get_y(navbar.buttons[COMPRESSION].rectangle.position)),
        button_dimension, 0, PRIMARY_COLOR, TRANSPARENT_COLOR);

    layout_manager(VERTICAL_CENTER, &navbar.rectangle, &navbar.buttons[EXTRACTION].rectangle, paddings);
    Image extract_icon = construct_image("assets/icons/extract.png", navbar.buttons[EXTRACTION].rectangle.position, button_dimension);
    add_button_image(&navbar.buttons[EXTRACTION], extract_icon, CENTER);

    navbar.buttons[VIEW] = construct_button(
        construct_position(get_x(navbar.buttons[EXTRACTION].rectangle.position) + get_width(button_dimension) + 36,
                           get_y(navbar.buttons[EXTRACTION].rectangle.position)),
        button_dimension, 0, PRIMARY_COLOR, TRANSPARENT_COLOR);
    layout_manager(VERTICAL_CENTER, &navbar.rectangle, &navbar.buttons[VIEW].rectangle, paddings);
    Image view_icon = construct_image("assets/icons/view.png", navbar.buttons[EXTRACTION].rectangle.position, button_dimension);
    add_button_image(&navbar.buttons[VIEW], view_icon, CENTER);

    navbar.buttons[DELETE] = construct_button(
        construct_position(
            get_x(navbar.buttons[VIEW].rectangle.position) + get_width(button_dimension) + 36, get_y(navbar.buttons[VIEW].rectangle.position)),
        button_dimension, 0, PRIMARY_COLOR, TRANSPARENT_COLOR);
    layout_manager(WEST, &navbar.rectangle, &navbar.buttons[DELETE].rectangle, paddings);
    Image delete_icon = construct_image("assets/icons/delete.png", navbar.buttons[VIEW].rectangle.position, button_dimension);
    add_button_image(&navbar.buttons[DELETE], delete_icon, CENTER);

    navbar.buttons[DESELECT] = construct_button(
        construct_position(get_x(navbar.buttons[DELETE].rectangle.position) - get_width(button_dimension) - 36,
                           get_y(navbar.buttons[DELETE].rectangle.position)),
        button_dimension, 0, PRIMARY_COLOR, TRANSPARENT_COLOR);
    layout_manager(VERTICAL_CENTER, &navbar.rectangle, &navbar.buttons[DESELECT].rectangle, paddings);
    Image deselect_icon = construct_image("assets/icons/deselect.png", navbar.buttons[DESELECT].rectangle.position, button_dimension);
    add_button_image(&navbar.buttons[DESELECT], deselect_icon, CENTER);

    return navbar;
}

void draw_navbar(NavBar navbar)
{
    draw_filled_rectangle(navbar.rectangle);
    for (int i = 0; i < number_of_buttons; i++)
    {
        draw_button(navbar.buttons[i]);
    }
}