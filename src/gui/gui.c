#include "pages/home/home.h"

void launch_graphical_interface()
{
    HomePage home_page = construct_home_page();
    while (1)
    {
        update_home_page(&home_page);
    }
}