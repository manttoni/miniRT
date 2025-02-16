#include "../includes/minirt.h"

void	cylinder_checks(int (**checks)(char *))
{
	checks[0] = &is_vector;
	checks[1] = &is_vector;
	checks[2] = &is_double;
	checks[3] = &is_double;
	checks[4] = &is_color;
	checks[5] = NULL;
}

int	assign_cylinder(t_object *cylinder, char **info)
{
	cylinder->location = parse_vector(info[1]);
	cylinder->orientation = parse_vector(info[2]);
	if (info[3][0] == '-')
		return (FAILURE);
	cylinder->diameter = parse_double(info[3]);
	cylinder->height = parse_double(info[4]);
	cylinder->color = parse_color(info[5]);
	cylinder->orientation = normalize_vector(cylinder->orientation); // delete this line before eval
	if (!is_normalized_vector(cylinder->orientation))
		return (failure("Cylinder orientation not normalized"));
	cylinder->collisionf = &cylinder_collision;
	return (SUCCESS);
}
