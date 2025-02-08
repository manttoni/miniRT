#include "../includes/minirt.h"

void    rotate_object(t_object *object, t_vector new_orientation)
{
    object->orientation = normalize_vector(new_orientation);
    if (object->type == CAMERA)
        object->info = image_plane(object);
}

void    translate_object(t_object *object, t_vector delta, t_object *camera)
{
    object->location = v_sum(object->location, delta);
    if (object->type == PLANE)
        precalculate_plane(object, camera);
}