#include "footer.h"

Footer construct_footer(Position position, Dimension dimension, char *text)
{
    Footer footer;

    footer.rectangle = construct_rectangle(position, dimension, 0, LIGHT_COLOR, LIGHT_COLOR);
    footer.text = construct_text(text, position, "assets/fonts/Roboto/Roboto-Black.ttf", 16, DARK_COLOR);
    layout_manager(WEST, &footer.rectangle, &footer.text.rectangle, construct_paddings(0, 25, 0, 0));

    return footer;
}

char *format_footer_text(int number_of_selected_elements, long total_size)
{
    char *footer_text = (char *)malloc(1000 * sizeof(char));
    double size_in_kb = total_size / 1024.0;
    double size_in_mb = size_in_kb / 1024.0;
    double size_in_gb = size_in_mb / 1024.0;

    if (size_in_gb >= 1.0)
    {
        sprintf(footer_text, "%d Elements selected - Total Size %.2f GB", number_of_selected_elements, size_in_gb);
    }
    else if (size_in_mb >= 1.0)
    {
        sprintf(footer_text, "%d Elements selected - Total Size %.2f MB", number_of_selected_elements, size_in_mb);
    }
    else if (size_in_kb >= 1.0)
    {
        sprintf(footer_text, "%d Elements selected - Total Size %.2f KB", number_of_selected_elements, size_in_kb);
    }
    else
    {
        sprintf(footer_text, "%d Elements selected - Total Size %ld bytes", number_of_selected_elements, total_size);
    }

    return footer_text;
}

void update_footer_text(Footer *footer, char *text)
{
    set_text_content(&footer->text, text);
}

void draw_footer(Footer footer)
{
    draw_filled_rectangle(footer.rectangle);
    draw_text(footer.text);
}