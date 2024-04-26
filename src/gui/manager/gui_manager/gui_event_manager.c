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
        int number_text_files = 0, i = 0;
        for (i = 0; i < graphical_interface->table.rows_to_compress.number_saved_files; i++)
        {
            if (!is_archive_file(graphical_interface->table.rows_to_compress.list[i].path))
            {
                paths[number_text_files] = graphical_interface->table.rows_to_compress.list[i].path;
                number_text_files++;
            }
        }

        if (number_text_files > 0)
        {
            Type compression_type = compute_compression_type(paths, number_text_files);
            char *archive_full_path = (char *)malloc(strlen(graphical_interface->explorer.current_directory.path) + strlen("/compressed.bin") + 1);
            strcpy(archive_full_path, graphical_interface->explorer.current_directory.path);
            archive_full_path = strcat(archive_full_path, "/compressed.bin");

            compress(paths, archive_full_path, number_text_files, compression_type);
            deselect_all(&graphical_interface->table);

            explore(&graphical_interface->explorer, graphical_interface->explorer.current_directory.path);
            order_explorer(&graphical_interface->explorer);

            clear_table_rows(&graphical_interface->table);
            update_table_rows(graphical_interface, graphical_interface->mouse_manager.wheel);
            free(paths);
            free(archive_full_path);
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
            explore(&graphical_interface->explorer, path);
            order_explorer(&graphical_interface->explorer);

            update_navbar_text(&graphical_interface->navbar, path);
            clear_table_rows(&graphical_interface->table);
            update_table_rows(graphical_interface, graphical_interface->mouse_manager.wheel);
        }
    }
}