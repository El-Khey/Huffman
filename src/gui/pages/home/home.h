#ifndef _HOME_PAGE_H
#define _HOME_PAGE_H

#include <stdio.h>
#include <stdlib.h>

#include "../../components/window/window.h"

typedef struct
{
    Window window;
} HomePage;

HomePage construct_home_page();
void update_home_page(HomePage *home_page);
void draw_home_page(HomePage *home_page);

#endif /** _HOME_PAGE_H */