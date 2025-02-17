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
	sphere->print_object = &print_sphere;
	return (SUCCESS);
}

void	print_sphere(t_object *s)
{
	printf("Sphere: ⚪\n");
	printf("Location: ");
	print_vector(s->location);
	printf("Diameter: %f\n", s->diameter);
	printf("Color: ");
	print_color(s->color);
}