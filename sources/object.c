#include "../includes/minirt.h"

t_type	get_type(char *line)
{
	char	*shapes[7];
	int		i;

	shapes[CAMERA] = "C ";
	shapes[LIGHT] = "L ";
	shapes[AMBIENT] = "A ";
	shapes[SPHERE] = "sp ";
	shapes[PLANE] = "pl ";
	shapes[CYLINDER] = "cy ";
	shapes[NONE] = NULL;
	i = 0;
	while (shapes[i] != NULL)
	{
		if (ft_strncmp(shapes[i], line, ft_strlen(shapes[i])) == 0)
		{
			return (i);
		}
		i++;
	}
	return (NONE);
}

int	assign_ambient(t_object *ambient, char **info)
{
	ambient->brightness = parse_double(info[1]);
	ambient->color = parse_color(info[2]);
	if (ambient->brightness < 0.0 || ambient->brightness > 1.0)
		return (failure("Brightness should be [0.0, 1.0]"));
	ambient->print_object = &print_ambient;
	return (SUCCESS);
}

int	assign_light(t_object *light, char **info)
{
	light->location = parse_vector(info[1]);
	light->brightness = parse_double(info[2]);
	if (light->brightness > 1.0 || light->brightness < 0.0)
		return (failure("Brightness should be [0.0, 1.0]"));
	light->print_object = &print_light;
	return (SUCCESS);
}

static int	assign_values(t_object *object, char **info)
{
	if (object == NULL || info == NULL)
		return (FAILURE);
	if (object->type == AMBIENT)
		return (assign_ambient(object, info));
	else if (object->type == CAMERA)
		return (assign_camera(object, info));
	else if (object->type == LIGHT)
		return (assign_light(object, info));
	else if (object->type == SPHERE)
		return (assign_sphere(object, info));
	else if (object->type == PLANE)
		return (assign_plane(object, info));
	else if (object->type == CYLINDER)
		return (assign_cylinder(object, info));
	return (FAILURE);
}

int	parse_object(t_object *object, char *line)
{
	char		**info;

	object->type = get_type(line);
	info = ft_split(line, ' ');
	if (assign_values(object, info) == FAILURE)
	{
		ft_free_array(info);
		failure("assign_values FAILURE");
		return (FAILURE);
	}
	ft_free_array(info);
	return (SUCCESS);
}
