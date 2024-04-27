#ifndef _THEME_H
#define _THEME_H

extern Color PRIMARY_COLOR;
extern Color SECONDARY_COLOR;
extern Color SPECIAL_COLOR;
extern Color TEXT_COLOR;

#define TRANSPARENT_COLOR construct_color(0.0, 0.0, 0.0, 0.0)

void light_theme();

void dark_theme();

int is_dark_theme();

#endif