#ifndef _PADDING_H
#define _PADDING_H

typedef struct
{
    int value;
} Padding;

typedef struct
{
    Padding top;
    Padding right;
    Padding bottom;
    Padding left;
} Paddings;

/**
 * @brief Construct a paddings object
 *
 * @param top
 * @param right
 * @param bottom
 * @param left
 * @return Paddings
 */
Paddings construct_paddings(int top, int right, int bottom, int left);

#endif