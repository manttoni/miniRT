#include "../includes/object.h"

void	create_sphere(t_object *object, char **info)
{
	object->type = SPHERE;
	object->diameter = parse_double(info[2]);
	object->color = parse_color(info[3]);
	if (parse_location(info[1], &(object->location)) < 0
		|| errno == EINVAL
		|| object->diameter < 0)
	{
		free(object);
		return ;
	}
	return ;
}

void	create_plane(t_object *object, char **info)
{
	object->type = PLANE;
	object->color = parse_color(info[3]);
	if (parse_location(info[1], &(object->location)) < 0
		|| parse_orientation(info[2], &(object->orientation)) < 0
		|| errno == EINVAL)
	{
		free(object);
		return ;
	}
	return ;
}

void	create_cylinder(t_object *object, char **info)
{
	object->type = CYLINDER;
	object->diameter = parse_double(info[3]);
	object->height = parse_double(info[4]);
	object->color = parse_color(info[5]);
	if (parse_location(info[1], &(object->location)) < 0
		|| parse_orientation(info[2], &(object->orientation)) < 0
		|| object->diameter < 0
		|| object->height < 0
		|| errno == EINVAL)
	{
		free(object);
		return ;
	}
	return ;
}
