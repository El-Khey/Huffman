#include "home.h"

HomePage construct_home_page()
{
    HomePage home_page;

    home_page.window = construct_window();
    MLV_create_window("Huffman Compressor", "Huffman Compressor", home_page.window.width, home_page.window.height);
    MLV_change_frame_rate(home_page.window.frame_rate);

    return home_page;
}

void update_home_page(HomePage *home_page)
{
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_actualise_window();
}
