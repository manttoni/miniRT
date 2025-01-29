
#include "../includes/minirt.h"

int	add_to_list(t_object **list, char *info)
{
	// t_object *object;

	// object = parse_object(info);
	// if (!object)
	// 	return (1);
	t_object *object;

	object = create_node(info);
	if (object == NULL || add_node(list, object))
	{
		// free(object);
		free_list(*list);
		*list = NULL;
		return (1);
	}
	print_list(*list);
	return (0);
}

t_object	*read_objects(char	*file)
{
	char		*line;
	int			fd;
	t_object		*list;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("failed to open file\n");
		return (NULL);
	}
	list = NULL;
	line = get_next_line(fd);
	while (line)
	{
		line = trim(line, '\n');
		if (*line != '#' && add_to_list(&list, line))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (list);
}
