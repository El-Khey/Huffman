#include "window.h"

Window construct_window()
{
    Window window;

    window.width = WINDOW_WIDTH;
    window.height = WINDOW_HEIGHT;
    window.frame_rate = 60;
    window.background_color = construct_color(0, 0, 0, 255);

    return window;
}
