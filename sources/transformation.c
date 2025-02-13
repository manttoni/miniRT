#include "../includes/minirt.h"

void rotate_object(t_object *object, t_vector new_orientation, t_data *data)
{
	object->orientation = normalize_vector(new_orientation);
	if (object->type == CAMERA)
		set_precalculations(data);
}

void translate_object(t_object *object, t_vector delta, t_data *data)
{
	object->location = v_sum(object->location, delta);
	if (object->type == PLANE || object->type == CAMERA || object->type == LIGHT)
		set_precalculations(data);
}

