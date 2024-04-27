#include "cross.h"

Cross construct_cross(Position position, Dimension dimension, Color color, int border_width)
{
    Cross cross;

    cross.position = position;
    cross.dimension = dimension;
    cross.color = color;
    cross.width = border_width;

    return cross;
}

void draw_cross(Cross cross)
{
    int i;

    int x1 = get_x(cross.position);
    int y1 = get_y(cross.position);

    int x2 = x1 + get_width(cross.dimension);
    int y2 = y1 + get_height(cross.dimension);

    MLV_Color color = convert_color(cross.color);

    /** Draw horizontal line with the specified border width */
    for (i = -cross.width / 2; i <= cross.width / 2; i++)
    {
        MLV_draw_line(x1, y1 + i, x2, y2 + i, color);
    }

    /** Draw vertical line with the specified border width */
    for (i = -cross.width / 2; i <= cross.width / 2; i++)
    {
        MLV_draw_line(x2 + i, y1, x1 + i, y2, color);
    }
}
