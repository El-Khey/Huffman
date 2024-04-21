#include "mouse_manager.h"

MouseManager construct_mouse_manager()
{
    MouseManager mouse_manager;
    mouse_manager.position = construct_position(0, 0);
    return mouse_manager;
}

void handle_mouse_events(MouseManager *mouse_manager)
{
    mouse_manager->last_mouse_state = mouse_manager->mouse_state;
    MLV_get_mouse_position(&mouse_manager->position.x, &mouse_manager->position.y);

    mouse_manager->mouse_state.right_click = MLV_get_mouse_button_state(MLV_BUTTON_RIGHT);
    mouse_manager->mouse_state.left_click = MLV_get_mouse_button_state(MLV_BUTTON_LEFT);

    if (mouse_manager->mouse_state.right_click == MLV_PRESSED && mouse_manager->last_mouse_state.right_click == MLV_RELEASED)
    {
        mouse_manager->mouse_event.click_count++;
        mouse_manager->mouse_event.is_right_click = 1;
    }
    else
    {
        mouse_manager->mouse_event.is_right_click = 0;
    }

    if (mouse_manager->mouse_state.left_click == MLV_PRESSED && mouse_manager->last_mouse_state.left_click == MLV_RELEASED)
    {
        mouse_manager->mouse_event.click_count++;
        mouse_manager->mouse_event.is_left_click = 1;
    }
    else
    {
        mouse_manager->mouse_event.is_left_click = 0;
    }
}

int is_right_button_clicked(MouseManager mouse_manager)
{
    return (mouse_manager.mouse_event.is_right_click == 1);
}

int is_left_button_clicked(MouseManager mouse_manager)
{
    return (mouse_manager.mouse_event.is_left_click == 1);
}

int is_mouse_clicked(MouseManager mouse_manager)
{
    return mouse_manager.mouse_event.click_count;
}

void set_mouse_released(MouseManager *mouse_manager)
{
    mouse_manager->mouse_event.click_count = 0;
}

Position get_mouse_position(MouseManager mouse_manager) { return mouse_manager.position; }