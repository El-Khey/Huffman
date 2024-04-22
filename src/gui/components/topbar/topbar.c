#include "topbar.h"

TopBar construct_topbar(Position position, Dimension dimension)
{
    TopBar topbar;

    topbar.rectangle = construct_rectangle(position, dimension, 0, PRIMARY_COLOR, TRANSPARENT_COLOR);
    add_border_to_rectangle(&topbar.rectangle, BORDER_BOTTOM, 5, SECONDARY_COLOR);
    Paddings paddings = construct_paddings(0, 22, 0, 22);

    Dimension button_dimension = construct_dimension(75, 90);

    topbar.buttons[COMPRESSION] = construct_button(construct_position(get_x(position), get_y(position)), button_dimension, 0, PRIMARY_COLOR, TRANSPARENT_COLOR);
    layout_manager(EAST, &topbar.rectangle, &topbar.buttons[COMPRESSION].rectangle, paddings);
    Image compress_icon = construct_image("assets/icons/compress.png", topbar.buttons[COMPRESSION].rectangle.position, button_dimension);
    add_button_image(&topbar.buttons[COMPRESSION], compress_icon, CENTER);

    topbar.buttons[EXTRACTION] = construct_button(
        construct_position(
            get_x(topbar.buttons[COMPRESSION].rectangle.position) + get_width(topbar.buttons[COMPRESSION].rectangle.dimension) + 36,
            get_y(topbar.buttons[COMPRESSION].rectangle.position)),
        button_dimension, 0, PRIMARY_COLOR, TRANSPARENT_COLOR);

    layout_manager(VERTICAL_CENTER, &topbar.rectangle, &topbar.buttons[EXTRACTION].rectangle, paddings);
    Image extract_icon = construct_image("assets/icons/extract.png", topbar.buttons[EXTRACTION].rectangle.position, button_dimension);
    add_button_image(&topbar.buttons[EXTRACTION], extract_icon, CENTER);

    topbar.buttons[VIEW] = construct_button(
        construct_position(get_x(topbar.buttons[EXTRACTION].rectangle.position) + get_width(button_dimension) + 36,
                           get_y(topbar.buttons[EXTRACTION].rectangle.position)),
        button_dimension, 0, PRIMARY_COLOR, TRANSPARENT_COLOR);
    layout_manager(VERTICAL_CENTER, &topbar.rectangle, &topbar.buttons[VIEW].rectangle, paddings);
    Image view_icon = construct_image("assets/icons/view.png", topbar.buttons[EXTRACTION].rectangle.position, button_dimension);
    add_button_image(&topbar.buttons[VIEW], view_icon, CENTER);

    topbar.buttons[DELETE] = construct_button(
        construct_position(
            get_x(topbar.buttons[VIEW].rectangle.position) + get_width(button_dimension) + 36, get_y(topbar.buttons[VIEW].rectangle.position)),
        button_dimension, 0, PRIMARY_COLOR, TRANSPARENT_COLOR);
    layout_manager(WEST, &topbar.rectangle, &topbar.buttons[DELETE].rectangle, paddings);
    Image delete_icon = construct_image("assets/icons/delete.png", topbar.buttons[VIEW].rectangle.position, button_dimension);
    add_button_image(&topbar.buttons[DELETE], delete_icon, CENTER);

    topbar.buttons[DESELECT] = construct_button(
        construct_position(get_x(topbar.buttons[DELETE].rectangle.position) - get_width(button_dimension) - 36,
                           get_y(topbar.buttons[DELETE].rectangle.position)),
        button_dimension, 0, PRIMARY_COLOR, TRANSPARENT_COLOR);
    layout_manager(VERTICAL_CENTER, &topbar.rectangle, &topbar.buttons[DESELECT].rectangle, paddings);
    Image deselect_icon = construct_image("assets/icons/deselect.png", topbar.buttons[DESELECT].rectangle.position, button_dimension);
    add_button_image(&topbar.buttons[DESELECT], deselect_icon, CENTER);

    return topbar;
}

void draw_topbar(TopBar topbar)
{
    draw_filled_rectangle(topbar.rectangle);
    for (int i = 0; i < number_of_buttons; i++)
    {
        draw_button(topbar.buttons[i]);
    }
}