#include "padding.h"

Paddings construct_paddings(int top, int right, int bottom, int left)
{
    Paddings paddings;

    paddings.top.value = top;
    paddings.right.value = right;
    paddings.bottom.value = bottom;
    paddings.left.value = left;

    return paddings;
}