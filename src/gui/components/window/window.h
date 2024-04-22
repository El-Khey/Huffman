#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#include "../navbar/navbar.h"
#include "../color/color.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600

typedef struct
{
    int width;
    int height;

    int frame_rate;
    Color background_color;
} Window;

Window construct_window();

void draw_window(Window window);

#endif /** WINDOW_H */