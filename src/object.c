#include "../inc/object.h"

t_object	*parse_object(char *line)
{
	char		**info;
	t_object	*object;

	object = NULL;
	info = ft_split(line, ' ');
	if (info == NULL)
		return (NULL);
	if (ft_strcmp(info[0], "A") == 0)
		object = create_ambient(info);
	else if (ft_strcmp(info[0], "C") == 0)
		object = create_camera(info);
	else if (ft_strcmp(info[0], "L") == 0)
		object = create_light(info);
	else if (ft_strcmp(info[0], "sp") == 0)
		object = create_sphere(info);
	else if (ft_strcmp(info[0], "pl") == 0)
		object = create_plane(info);
	else if (ft_strcmp(info[0], "cy") == 0)
		object = create_cylinder(info);
	else
		printf("Wrong identifier!\n");
	free_array(info);
	return (object);
}
