#include "../includes/object.h"

t_object	*create_sphere(char **info)
{
	t_object	*sphere;

	sphere = ft_calloc(1, sizeof(t_object));
	if (sphere == NULL)
		return (NULL);
	sphere->type = SPHERE;
	sphere->diameter = parse_double(info[2]);
	sphere->color = parse_color(info[3]);
	if (parse_location(info[1], &(sphere->location)) < 0
		|| errno == EINVAL
		|| sphere->diameter < 0)
	{
		free(sphere);
		return (NULL);
	}
	sphere->collision = &sphere_collision;
	return (sphere);
}

t_object	*create_plane(char **info)
{
	t_object	*plane;

	plane = ft_calloc(1, sizeof(t_object));
	if (plane == NULL)
		return (NULL);
	plane->type = PLANE;
	plane->color = parse_color(info[3]);
	if (parse_location(info[1], &(plane->location)) < 0
		|| parse_orientation(info[2], &(plane->orientation)) < 0
		|| errno == EINVAL)
	{
		free(plane);
		return (NULL);
	}
	plane->collision = &plane_collision;
	return (plane);
}

t_object	*create_cylinder(char **info)
{
	t_object	*cylinder;

	cylinder = ft_calloc(1, sizeof(t_object));
	if (cylinder == NULL)
		return (NULL);
	cylinder->type = CYLINDER;
	cylinder->diameter = parse_double(info[3]);
	cylinder->height = parse_double(info[4]);
	cylinder->color = parse_color(info[5]);
	if (parse_location(info[1], &(cylinder->location)) < 0
		|| parse_orientation(info[2], &(cylinder->orientation)) < 0
		|| cylinder->diameter < 0
		|| cylinder->height < 0
		|| errno == EINVAL)
	{
		free(cylinder);
		return (NULL);
	}
	return (cylinder);
}
