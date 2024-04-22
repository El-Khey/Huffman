#ifndef _HOME_PAGE_H
#define _HOME_PAGE_H

#include <stdio.h>
#include <stdlib.h>

#include "../../components/window/window.h"
#include "../../manager/mouse_manager/mouse_manager.h"

typedef struct
{
    MouseManager mouse_manager;
    Window window;
    NavBar navbar;
} HomePage;

/**
 * @brief Construct the home page
 *
 * @return HomePage - the home page
 */
HomePage construct_home_page();

/**
 * @brief Update the home page
 *
 * @param home_page - the home page
 */
void update_home_page(HomePage *home_page);

/**
 * @brief Draw the home page
 *
 * @param home_page - the home page
 */
void draw_home_page(HomePage home_page);

#endif /** _HOME_PAGE_H */