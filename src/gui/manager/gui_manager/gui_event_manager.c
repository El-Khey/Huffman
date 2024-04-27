#include "gui_manager.h"

void handle_scroll_bar_event(GraphicalInterface *graphical_interface)
{
    if (is_rectangle_hovered(graphical_interface->table.rectangle, get_mouse_position(graphical_interface->mouse_manager)))
    {
        handle_mouse_wheel_event(&graphical_interface->mouse_manager);
        if (is_wheel_scrolled(graphical_interface->mouse_manager))
        {
            int direction = graphical_interface->mouse_manager.wheel - graphical_interface->mouse_manager.previous_wheel;
            direction = direction > 0 ? 1 : -1;
            clear_table_rows(&graphical_interface->table);
            update_table_rows(graphical_interface, direction);
            graphical_interface->mouse_manager.previous_wheel = graphical_interface->mouse_manager.wheel;
        }
    }
}

void handle_navbar_back_event(GraphicalInterface *graphical_interface)
{
    if (is_button_clicked(graphical_interface->navbar.back, graphical_interface->mouse_manager))
    {
        char *parent_directory = get_parent_directory(graphical_interface->explorer.current_directory.path);
        parent_directory[strlen(parent_directory) - 1] = '\0';

        explore(&graphical_interface->explorer, parent_directory);
        order_explorer(&graphical_interface->explorer);

        update_navbar_text(&graphical_interface->navbar, parent_directory);
        clear_table_rows(&graphical_interface->table);
        update_table_rows(graphical_interface, graphical_interface->mouse_manager.wheel);
    }
}

void handle_deselect_all_event(GraphicalInterface *graphical_interface)
{
    if (is_button_clicked(graphical_interface->topbar.buttons[DESELECT], graphical_interface->mouse_manager))
    {
        deselect_all(&graphical_interface->table);
    }
}

void handle_delete_event(GraphicalInterface *graphical_interface)
{
    if (is_button_clicked(graphical_interface->topbar.buttons[DELETE], graphical_interface->mouse_manager))
    {
        for (int i = 0; i < graphical_interface->table.rows_to_compress.number_saved_files; i++)
        {
            delete_file_or_directory(graphical_interface->table.rows_to_compress.list[i].path);
        }

        graphical_interface->table.rows_to_compress.number_saved_files = 0;
        graphical_interface->table.rows_to_compress.total_size = 0;
        update_footer_text(&graphical_interface->footer, format_footer_text(graphical_interface->table.rows_to_compress.number_saved_files, graphical_interface->table.rows_to_compress.total_size));

        explore(&graphical_interface->explorer, graphical_interface->explorer.current_directory.path);
        order_explorer(&graphical_interface->explorer);

        clear_table_rows(&graphical_interface->table);
        update_table_rows(graphical_interface, graphical_interface->mouse_manager.wheel);
    }
}

void handle_compress_event(GraphicalInterface *graphical_interface)
{
    if (is_button_clicked(graphical_interface->topbar.buttons[COMPRESS], graphical_interface->mouse_manager))
    {
        char **paths = (char **)malloc(graphical_interface->table.rows_to_compress.number_saved_files * sizeof(char *));
        int number_paths = 0, i = 0;

        for (i = 0; i < graphical_interface->table.rows_to_compress.number_saved_files; i++)
        {
            if (!is_archive_file(graphical_interface->table.rows_to_compress.list[i].path))
            {
                paths[number_paths] = (char *)malloc(strlen(graphical_interface->table.rows_to_compress.list[i].path) + 1);
                strcpy(paths[number_paths], graphical_interface->table.rows_to_compress.list[i].path);
                number_paths++;
            }
        }

        if (number_paths > 0)
        {
            Type compression_type = compute_compression_type(paths, number_paths);
            char *archive_full_path = (char *)malloc(strlen(graphical_interface->explorer.current_directory.path) + strlen("/compressed.bin") + 1);
            strcpy(archive_full_path, graphical_interface->explorer.current_directory.path);
            archive_full_path = strcat(archive_full_path, "/compressed.bin");

            compress(paths, archive_full_path, number_paths, compression_type);
            deselect_all(&graphical_interface->table);

            explore(&graphical_interface->explorer, graphical_interface->explorer.current_directory.path);
            order_explorer(&graphical_interface->explorer);

            clear_table_rows(&graphical_interface->table);
            update_table_rows(graphical_interface, graphical_interface->mouse_manager.wheel);
        }
    }
}

void handle_rows_button_event(GraphicalInterface *graphical_interface)
{
    for (int i = 0; i < graphical_interface->table.row_index; i++)
    {
        if (is_button_clicked(graphical_interface->table.rows[i].button, graphical_interface->mouse_manager))
        {
            char *path = graphical_interface->table.rows[i].path;
            if (is_text_file(path) || is_archive_file(path))
            {
                // TODO: A TESTER
                char *command = (char *)malloc(strlen("xdg-open ") + strlen(path) + 1);
                strcpy(command, "xdg-open ");
                command = strcat(command, path);
                system(command);
                return;
            }

            explore(&graphical_interface->explorer, path);
            order_explorer(&graphical_interface->explorer);

            update_navbar_text(&graphical_interface->navbar, path);
            clear_table_rows(&graphical_interface->table);
            update_table_rows(graphical_interface, graphical_interface->mouse_manager.wheel);
        }
    }
}

static void update_theme(GraphicalInterface *graphical_interface)
{
    graphical_interface->window.background_color = PRIMARY_COLOR;

    graphical_interface->topbar.rectangle.background_color = PRIMARY_COLOR;
    graphical_interface->topbar.buttons[DESELECT].rectangle.background_color = PRIMARY_COLOR;
    graphical_interface->topbar.buttons[DELETE].rectangle.background_color = PRIMARY_COLOR;
    graphical_interface->topbar.buttons[COMPRESS].rectangle.background_color = PRIMARY_COLOR;
    graphical_interface->topbar.buttons[EXTRACTION].rectangle.background_color = PRIMARY_COLOR;
    graphical_interface->topbar.buttons[VIEW].rectangle.background_color = PRIMARY_COLOR;

    graphical_interface->navbar.background.background_color = PRIMARY_COLOR;
    add_border_to_rectangle(&graphical_interface->navbar.background, BORDER_TOP, 5, SPECIAL_COLOR);
    add_border_to_rectangle(&graphical_interface->navbar.background, BORDER_BOTTOM, 5, SPECIAL_COLOR);

    add_border_to_rectangle(&graphical_interface->navbar.displayed_path.rectangle, BORDER_BOTTOM, 2, TEXT_COLOR);
    add_border_to_rectangle(&graphical_interface->navbar.displayed_path.rectangle, BORDER_TOP, 2, TEXT_COLOR);
    add_border_to_rectangle(&graphical_interface->navbar.displayed_path.rectangle, BORDER_LEFT, 2, TEXT_COLOR);
    add_border_to_rectangle(&graphical_interface->navbar.displayed_path.rectangle, BORDER_RIGHT, 2, TEXT_COLOR);
    graphical_interface->navbar.displayed_path.color = TEXT_COLOR;

    graphical_interface->table.background_color = TRANSPARENT_COLOR;
    graphical_interface->table.text_color = TEXT_COLOR;

    graphical_interface->footer.rectangle.background_color = PRIMARY_COLOR;
    graphical_interface->footer.text.color = TEXT_COLOR;

    graphical_interface->footer.theme_button.rectangle.background_color = SPECIAL_COLOR;
    graphical_interface->footer.theme_button.text.color = TEXT_COLOR;

    for (int i = 0; i < graphical_interface->table.column_index; i++)
    {
        graphical_interface->table.columns[i].text.color = TEXT_COLOR;
    }

    for (int i = 0; i < graphical_interface->table.row_index; i++)
    {
        graphical_interface->table.rows[i].checkbox.button.rectangle.background_color = PRIMARY_COLOR;
        add_border_to_rectangle(&graphical_interface->table.rows[i].checkbox.button.rectangle, BORDER_TOP, 2, TEXT_COLOR);
        add_border_to_rectangle(&graphical_interface->table.rows[i].checkbox.button.rectangle, BORDER_BOTTOM, 2, TEXT_COLOR);
        add_border_to_rectangle(&graphical_interface->table.rows[i].checkbox.button.rectangle, BORDER_LEFT, 2, TEXT_COLOR);
        add_border_to_rectangle(&graphical_interface->table.rows[i].checkbox.button.rectangle, BORDER_RIGHT, 2, TEXT_COLOR);

        graphical_interface->table.rows[i].checkbox.checked_color = SPECIAL_COLOR;
        graphical_interface->table.rows[i].checkbox.default_color = PRIMARY_COLOR;

        graphical_interface->table.rows[i].button.text.color = TEXT_COLOR;
        graphical_interface->table.rows[i].filename.color = TEXT_COLOR;
        graphical_interface->table.rows[i].size.color = TEXT_COLOR;
        graphical_interface->table.rows[i].type.color = TEXT_COLOR;
        graphical_interface->table.rows[i].last_modified.color = TEXT_COLOR;
    }
}

void handle_theme_button_event(GraphicalInterface *graphical_interface)
{
    if (is_button_clicked(graphical_interface->footer.theme_button, graphical_interface->mouse_manager))
    {
        if (is_dark_theme())
        {
            light_theme();
            set_text_content(&graphical_interface->footer.theme_button.text, "Dark Theme");
        }
        else
        {
            dark_theme();
            set_text_content(&graphical_interface->footer.theme_button.text, "Light Theme");
        }
        update_theme(graphical_interface);
        layout_manager(CENTER, &graphical_interface->footer.theme_button.rectangle, &graphical_interface->footer.theme_button.text.rectangle, construct_paddings(0, 0, 0, 0));
    }
}