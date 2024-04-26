#include "gui.h"

static void initialize_table_header(GraphicalInterface *graphical_interface);
static void initialize_table_rows(GraphicalInterface *graphical_interface, int direction);

GraphicalInterface construct_graphical_interface()
{
    GraphicalInterface graphical_interface;
    char *absolute_path = get_absolute_path(".");

    graphical_interface.window = construct_window();
    graphical_interface.topbar = construct_topbar(construct_position(0, 0), construct_dimension(TOP_BAR_WIDTH, TOP_BAR_HEIGHT));
    graphical_interface.navbar = construct_navbar(construct_position(0, TOP_BAR_HEIGHT), construct_dimension(NAV_BAR_WIDTH, NAV_BAR_HEIGHT));

    graphical_interface.mouse_manager = construct_mouse_manager();
    graphical_interface.explorer = construct_explorer();

    explore(&graphical_interface.explorer, absolute_path);
    update_navbar_text(&graphical_interface.navbar, absolute_path);

    order_directories(&graphical_interface.explorer.directories);
    order_files(&graphical_interface.explorer.files);

    initialize_table_header(&graphical_interface);
    initialize_table_rows(&graphical_interface, graphical_interface.mouse_manager.wheel);

    graphical_interface.footer = construct_footer(construct_position(0, WINDOW_HEIGHT - FOOTER_HEIGHT),
                                                  construct_dimension(WINDOW_WIDTH, FOOTER_HEIGHT),
                                                  "0 Elements selected - Total Size 0 byte ");
    return graphical_interface;
}

void launch_graphical_interface()
{
    GraphicalInterface graphical_interface = construct_graphical_interface();
    while (1)
    {
        update_graphical_interface(&graphical_interface);
        draw_graphical_interface(graphical_interface);
    }
}

static void initialize_table_header(GraphicalInterface *graphical_interface)
{
    graphical_interface->table = construct_table(construct_position(0, TOP_BAR_HEIGHT + NAV_BAR_HEIGHT),
                                                 construct_dimension(WINDOW_WIDTH, WINDOW_HEIGHT - TOP_BAR_HEIGHT - NAV_BAR_HEIGHT),
                                                 10, 6, TRANSPARENT_COLOR, LIGHT_COLOR);
    add_column(&graphical_interface->table, construct_position(25, get_y(graphical_interface->table.rectangle.position)), construct_dimension(100, 50), "");
    add_column(&graphical_interface->table, construct_position(50, get_y(graphical_interface->table.rectangle.position)), construct_dimension(50, 50), "");
    add_column(&graphical_interface->table, construct_position(125, get_y(graphical_interface->table.rectangle.position)), construct_dimension(150, 50), "Name");
    add_column(&graphical_interface->table, construct_position(400, get_y(graphical_interface->table.rectangle.position)), construct_dimension(50, 50), "Size");
    add_column(&graphical_interface->table, construct_position(550, get_y(graphical_interface->table.rectangle.position)), construct_dimension(100, 50), "Type");
    add_column(&graphical_interface->table, construct_position(800, get_y(graphical_interface->table.rectangle.position)), construct_dimension(100, 50), "Last Modified");
}

static void initialize_table_rows(GraphicalInterface *graphical_interface, int direction)
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

void update_graphical_interface(GraphicalInterface *graphical_interface)
{
    handle_mouse_events(&graphical_interface->mouse_manager);
    handle_table_selection(&graphical_interface->table, graphical_interface->mouse_manager);

    update_footer_text(&graphical_interface->footer, format_footer_text(graphical_interface->table.rows_to_compress.number_saved_files, graphical_interface->table.rows_to_compress.total_size));
    if (is_rectangle_hovered(graphical_interface->table.rectangle, get_mouse_position(graphical_interface->mouse_manager)))
    {
        handle_mouse_wheel_event(&graphical_interface->mouse_manager);
        if (is_wheel_scrolled(graphical_interface->mouse_manager))
        {
            int direction = graphical_interface->mouse_manager.wheel - graphical_interface->mouse_manager.previous_wheel;
            direction = direction > 0 ? 1 : -1;
            clear_table_rows(&graphical_interface->table);
            initialize_table_rows(graphical_interface, direction);
            graphical_interface->mouse_manager.previous_wheel = graphical_interface->mouse_manager.wheel;
        }
    }
    else if (is_button_clicked(graphical_interface->navbar.back, graphical_interface->mouse_manager))
    {
        char *parent_directory = get_parent_directory(graphical_interface->explorer.current_directory.path);
        parent_directory[strlen(parent_directory) - 1] = '\0';

        explore(&graphical_interface->explorer, parent_directory);
        order_directories(&graphical_interface->explorer.directories);
        order_files(&graphical_interface->explorer.files);

        update_navbar_text(&graphical_interface->navbar, parent_directory);
        clear_table_rows(&graphical_interface->table);
        initialize_table_rows(graphical_interface, graphical_interface->mouse_manager.wheel);
    }
    else if (is_button_clicked(graphical_interface->topbar.buttons[DESELECT], graphical_interface->mouse_manager))
    {
        deselect_all(&graphical_interface->table);
    }
    else if (is_button_clicked(graphical_interface->topbar.buttons[DELETE], graphical_interface->mouse_manager))
    {
        for (int i = 0; i < graphical_interface->table.rows_to_compress.number_saved_files; i++)
        {
            delete_file_or_directory(graphical_interface->table.rows_to_compress.list[i].path);
        }

        graphical_interface->table.rows_to_compress.number_saved_files = 0;
        graphical_interface->table.rows_to_compress.total_size = 0;
        update_footer_text(&graphical_interface->footer, format_footer_text(graphical_interface->table.rows_to_compress.number_saved_files, graphical_interface->table.rows_to_compress.total_size));

        explore(&graphical_interface->explorer, graphical_interface->explorer.current_directory.path);
        order_directories(&graphical_interface->explorer.directories);
        order_files(&graphical_interface->explorer.files);

        clear_table_rows(&graphical_interface->table);
        initialize_table_rows(graphical_interface, graphical_interface->mouse_manager.wheel);
    }
    else if (is_button_clicked(graphical_interface->topbar.buttons[COMPRESS], graphical_interface->mouse_manager))
    {
        char **paths = (char **)malloc(graphical_interface->table.rows_to_compress.number_saved_files * sizeof(char *));
        int number_text_files = 0;
        for (int i = 0; i < graphical_interface->table.rows_to_compress.number_saved_files; i++)
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
            order_directories(&graphical_interface->explorer.directories);
            order_files(&graphical_interface->explorer.files);

            clear_table_rows(&graphical_interface->table);
            initialize_table_rows(graphical_interface, graphical_interface->mouse_manager.wheel);
        }
    }

    for (int i = 0; i < graphical_interface->table.row_index; i++)
    {
        if (is_button_clicked(graphical_interface->table.rows[i].button, graphical_interface->mouse_manager))
        {
            char *path = graphical_interface->table.rows[i].path;
            explore(&graphical_interface->explorer, path);
            order_directories(&graphical_interface->explorer.directories);
            order_files(&graphical_interface->explorer.files);

            update_navbar_text(&graphical_interface->navbar, path);
            clear_table_rows(&graphical_interface->table);
            initialize_table_rows(graphical_interface, graphical_interface->mouse_manager.wheel);
        }
    }
}

void draw_graphical_interface(GraphicalInterface graphical_interface)
{
    draw_window(graphical_interface.window);
    draw_topbar(graphical_interface.topbar);
    draw_navbar(graphical_interface.navbar);
    draw_table(graphical_interface.table);
    draw_footer(graphical_interface.footer);
}
