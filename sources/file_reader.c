#include "../includes/minirt.h"
#include <fcntl.h>

t_node	*read_objects(char	*file)
{
	char		*line;
	int			fd;
	t_node		*list;

	if (ft_strcmp(ft_strrchr(file, '.'), ".rt") != 0
		|| ft_countchar(file, '.') != 1)
	{
		printf("wrong type of file\n");
		return (NULL);
	}
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
		//printf("line: %s\n", line);
		if (add_node(&list, create_node(parse_object(line))) < 0)
		{
			printf("add node failed\n");
			close(fd);
			return (NULL);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (list);
}
