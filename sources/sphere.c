#include "../includes/minirt.h"

void	sphere_checks(int (**checks)(char *))
{
		checks[0] = &is_vector;
		checks[1] = &is_double;
		checks[2] = &is_color;
		checks[3] = NULL;
}


int	assign_sphere(t_object *sphere, char **info)
{
	sphere->location = parse_vector(info[1]);
	if (info[2][0] == '-')
		return (FAILURE);
	sphere->diameter = parse_double(info[2]);
	sphere->color = parse_color(info[3]);
	sphere->collisionf = &sphere_collision;
	return (SUCCESS);
}
