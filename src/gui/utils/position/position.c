#include "position.h"

Position construct_position(int x, int y)
{
    Position p;
    p.x = x;
    p.y = y;

    return p;
}

int get_x(Position p) { return p.x; }

int get_y(Position p) { return p.y; }

void set_x(Position *p, int x) { p->x = x; }

void set_y(Position *p, int y) { p->y = y; }

void move_y(Position *p, int dy) { p->y += dy; }

void move_x(Position *p, int dx) { p->x += dx; }

void move_position(Position *p, int dx, int dy)
{
    p->x += dx;
    p->y += dy;
}

void print_position(Position p)
{
    printf("Position: (%d, %d)\n", p.x, p.y);
}