#include "../includes/minirt.h"

void rotate_object(t_object *object, t_vector new_orientation, t_objarr *objarr)
{
	object->orientation = normalize_vector(new_orientation);
	if (object->type == CAMERA)
		set_precalculations(objarr);
}

void translate_object(t_object *object, t_vector delta, t_objarr *objarr)
{
	object->location = v_sum(object->location, delta);
	if (object->type == PLANE || object->type == CAMERA)
		set_precalculations(objarr);
}

