#include "../includes/minirt.h"

void	rotate_object(t_object *object, t_vector new_orientation)
{
	object->orientation = normalize_vector(new_orientation);
	print_vector(object->orientation);
}

void	translate_object(t_object *object, t_vector delta)
{
	object->location = v_sum(object->location, delta);
	print_vector(object->location);
}
