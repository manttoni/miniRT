#include "../inc/object.h"

t_object	*create_sphere(char **info)
{
	t_object	*sphere;

	sphere = ft_calloc(1, sizeof(t_object));
	if (sphere == NULL)
		return (NULL);
	sphere->type = SPHERE;
	sphere->location = parse_location(info[1]);
	sphere->diameter = parse_udouble(info[2]);
	sphere->color = parse_color(info[3]);
	sphere->collision = sphere_collision;
	// inset error handling here
	return (sphere);
}

t_object	*create_plane(char **info)
{
	t_object	*plane;

	plane = ft_calloc(1, sizeof(t_object));
	if (plane == NULL)
		return (NULL);
	plane->type = PLANE;
	plane->location = parse_location(info[1]);
	plane->orientation = parse_orientation(info[2]);
	plane->color = parse_color(info[3]);
	plane->collision = sphere_collision;
	// insert error handling here
	return (plane);
}

t_object	*create_cylinder(char **info)
{
	t_object	*cylinder;

	cylinder = ft_calloc(1, sizeof(t_object));
	if (cylinder == NULL)
		return (NULL);
	cylinder->type = CYLINDER;
	cylinder->location = parse_location(info[1]);
	cylinder->orientation = parse_orientation(info[2]);
	cylinder->diameter = parse_udouble(info[3]);
	cylinder->height = parse_udouble(info[4]);
	cylinder->color = parse_color(info[5]);
	cylinder->collision = cylinder_collision;
	// insert error handling here
	return (cylinder);
}
