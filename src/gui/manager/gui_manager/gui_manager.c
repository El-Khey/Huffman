#include "../../gui.h"

void update_table_rows(GraphicalInterface *graphical_interface, int direction)
{
    graphical_interface->table.scroll_index += direction;
    graphical_interface->table.scroll_index = max(graphical_interface->table.scroll_index, 0);

    int total_rows = graphical_interface->explorer.directories.number_of_directories + graphical_interface->explorer.files.number_of_files;
    int max_index = max(total_rows - graphical_interface->table.max_rows, 0);
    graphical_interface->table.scroll_index = min(graphical_interface->table.scroll_index, max_index);

    int i = graphical_interface->table.scroll_index;
    int displayed_rows = 0;

    // Loop until the maximum number of rows are displayed
    while (i < total_rows && displayed_rows < graphical_interface->table.max_rows)
    {
        // Add directory row if available
        if (i < graphical_interface->explorer.directories.number_of_directories)
        {
            add_row(&graphical_interface->table, graphical_interface->explorer.directories.list[i].path,
                    graphical_interface->explorer.directories.list[i].name, graphical_interface->explorer.directories.list[i].metadata.size,
                    graphical_interface->explorer.directories.list[i].metadata.type, graphical_interface->explorer.directories.list[i].metadata.last_modified);
            displayed_rows++;
        }

        // Add file row if available
        else if (i - graphical_interface->explorer.directories.number_of_directories < graphical_interface->explorer.files.number_of_files)
        {
            int file_index = i - graphical_interface->explorer.directories.number_of_directories;
            add_row(&graphical_interface->table, graphical_interface->explorer.files.list[file_index].path,
                    graphical_interface->explorer.files.list[file_index].name, graphical_interface->explorer.files.list[file_index].metadata.size,
                    graphical_interface->explorer.files.list[file_index].metadata.type, graphical_interface->explorer.files.list[file_index].metadata.last_modified);
            displayed_rows++;
        }
        i++;
    }

    // if the created rows are present inside the DocToCompress list, check the checkbox
    for (int i = 0; i < graphical_interface->table.rows_to_compress.number_saved_files; i++)
    {
        for (int j = 0; j < graphical_interface->table.row_index; j++)
        {
            if (strcmp(graphical_interface->table.rows[j].path, graphical_interface->table.rows_to_compress.list[i].path) == 0)
            {
                check(&graphical_interface->table.rows[j].checkbox);
            }
        }
    }
}

void manage_gui_event(GraphicalInterface *graphical_interface)
{
    handle_scroll_bar_event(graphical_interface);
    handle_navbar_back_event(graphical_interface);
    handle_deselect_all_event(graphical_interface);
    handle_delete_event(graphical_interface);
    handle_rows_button_event(graphical_interface);
    handle_compress_event(graphical_interface);
    handle_theme_button_event(graphical_interface);
}