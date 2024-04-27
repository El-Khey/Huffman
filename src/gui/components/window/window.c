#include "window.h"

Window construct_window()
{
    Window window;

    window.width = WINDOW_WIDTH;
    window.height = WINDOW_HEIGHT;
    window.frame_rate = 60;
    window.background_color = PRIMARY_COLOR;

    MLV_create_window("Huffman Compressor", "Huffman Compressor", window.width, window.height);
    MLV_change_frame_rate(window.frame_rate);

    return window;
}

void draw_window(Window window)
{
    MLV_actualise_window();
    MLV_clear_window(convert_color(window.background_color));
}