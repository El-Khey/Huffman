#ifndef _LAYOU_MANAGER_H
#define _LAYOU_MANAGER_H

#include <stdio.h>
#include <stdlib.h>

#include "../../components/shape/rectangle/rectangle.h"
#include "../../components/padding/padding.h"
#include "../../utils/dimension/dimension.h"
#include "../../utils/position/position.h"

typedef enum
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
    NORTH_EAST,
    NORTH_WEST,
    SOUTH_EAST,
    SOUTH_WEST,
    VERTICAL_CENTER,
    HORIZONTAL_CENTER,
    CENTER
} LayoutType;

/**
 * @brief Définit la position du rectangle enfant par rapport au rectangle parent
 *
 * @param layout_type Le type de positionnement
 * @param parent Le rectangle parent
 * @param child Le rectangle enfant
 */
void layout_manager(LayoutType layout_type, Rectangle *parent, Rectangle *child, Paddings paddings);

#endif