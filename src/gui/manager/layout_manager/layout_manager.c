#include "layout_manager.h"

void layout_manager(LayoutType layout_type, Rectangle *parent, Rectangle *child, Paddings paddings)
{
    switch (layout_type)
    {
    case NORTH:
        set_position(&child->position, get_x(parent->position) + (get_width(parent->dimension) - get_width(child->dimension)) / 2, get_y(parent->position) + paddings.top.value);
        break;
    case SOUTH:
        set_position(&child->position, get_x(parent->position) + (get_width(parent->dimension) - get_width(child->dimension)) / 2, get_y(parent->position) + get_height(parent->dimension) - get_height(child->dimension) - paddings.bottom.value);
        break;
    case EAST:
        set_position(&child->position, get_x(parent->position) + paddings.left.value, get_y(parent->position) + (get_height(parent->dimension) - get_height(child->dimension)) / 2);
        break;
    case WEST:
        set_position(&child->position, get_x(parent->position) + get_width(parent->dimension) - get_width(child->dimension) - paddings.right.value, get_y(parent->position) + (get_height(parent->dimension) - get_height(child->dimension)) / 2);
        break;
    case SOUTH_EAST:
        set_position(&child->position, get_x(parent->position) + paddings.left.value, get_y(parent->position) + get_height(parent->dimension) - get_height(child->dimension) - paddings.bottom.value);
        break;
    case NORTH_EAST:
        set_position(&child->position, get_x(parent->position) + paddings.left.value, get_y(parent->position) + paddings.top.value);
        break;
    case NORTH_WEST:
        set_position(&child->position, get_x(parent->position) + get_width(parent->dimension) - get_width(child->dimension) - paddings.right.value, get_y(parent->position) + paddings.top.value);
        break;
    case SOUTH_WEST:
        set_position(&child->position, get_x(parent->position) + get_width(parent->dimension) - get_width(child->dimension) - paddings.right.value, get_y(parent->position) + get_height(parent->dimension) - get_height(child->dimension) - paddings.bottom.value);
        break;
    case VERTICAL_CENTER:
        set_y(&child->position, get_y(parent->position) + (get_height(parent->dimension) - get_height(child->dimension)) / 2 + paddings.top.value - paddings.bottom.value);
        break;
    case HORIZONTAL_CENTER:
        set_x(&child->position, get_x(parent->position) + (get_width(parent->dimension) - get_width(child->dimension)) / 2 + paddings.left.value - paddings.right.value);
        break;
    case CENTER:
        set_position(&child->position, get_x(parent->position) + (get_width(parent->dimension) - get_width(child->dimension)) / 2 + paddings.left.value - paddings.right.value, get_y(parent->position) + (get_height(parent->dimension) - get_height(child->dimension)) / 2 + paddings.top.value - paddings.bottom.value);
        break;
    default:
        break;
    }
}
