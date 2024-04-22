#include "image.h"

Image construct_image(char *path, Position position, Dimension dimension)
{
    Image image;

    MLV_Image *loaded_image = MLV_load_image(path);
    is_image_loaded_successfully(loaded_image, path);
    MLV_resize_image(loaded_image, dimension.width, dimension.height);

    image.image = loaded_image;
    image.rectangle.dimension = dimension;
    image.rectangle.position = position;

    strcpy(image.path, path);
    return image;
}

Dimension get_image_dimension(MLV_Image *image)
{
    Dimension dimension;
    MLV_get_image_size(image, &dimension.width, &dimension.height);
    return dimension;
}

int is_image_loaded_successfully(MLV_Image *image, char *path)
{
    if (!image)
    {
        fprintf(stderr, "Image not found at path : %s\n", path);
        exit(1);
    }

    return 1;
}

void vertical_image_mirror(Image *image)
{
    MLV_vertical_image_mirror(image->image);
}

void set_image_position(Image *image, Position position)
{
    image->rectangle.position = position;
}

void set_image_dimension(Image *image, Dimension dimension)
{
    image->rectangle.dimension = dimension;
}

void draw_image(Image *image)
{
    MLV_draw_image(image->image, get_x(image->rectangle.position), get_y(image->rectangle.position));
}

void free_image(Image *image)
{
    MLV_free_image(image->image);
    image->image = NULL;
}