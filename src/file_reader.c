#include "../lib/get_next_line/get_next_line.h"
#include "../inc/minirt.h"
#include <fcntl.h>

t_node	*read_objects(char	*file)
{
	char		*line;
	int			fd;
	t_node		*list;
	t_node		*new;
	t_object	*object;

	if (ft_strcmp(ft_strrchr(file, '.'), ".rt") != 0
		|| ft_countchar(file, '.') != 1)
	{
		return (NULL);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		return (NULL);
	}
	list = NULL;
	line = get_next_line(fd);
	while (line)
	{
		line = trim(line, '\n');
		printf("%s\n", line);
		if (add_node(&list, create_node(parse_object(line))) < 0)
		{
			close(fd);
			return (NULL);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (list);
}
