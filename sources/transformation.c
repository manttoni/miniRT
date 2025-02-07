#include "../includes/minirt.h"

void    rotate_object(t_object *object, t_vector new_orientation)
{
    object->orientation = new_orientation;
    if (object->type == CAMERA)
        object->info = image_plane(object);
}