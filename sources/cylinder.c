#include "../includes/minirt.h"

int	assign_cylinder(t_object *cylinder, char **info)
{
	cylinder->location = parse_vector(info[1]);
	cylinder->orientation = parse_vector(info[2]);
	if (info[3][0] == '-')
		return (FAILURE);
	cylinder->diameter = parse_double(info[3]);
	cylinder->height = parse_double(info[4]);
	cylinder->color = parse_color(info[5]);
	cylinder->orientation = normalize_vector(cylinder->orientation);
	// if (!is_normalized_vector(cylinder->orientation))
	// 	return (failure("Cylinder orientation not normalized"));
	cylinder->collisionf = &cylinder_collision;
	return (SUCCESS);
}