#include "../includes/minirt.h"


t_node	*read_objects(char	*file)
{
	char		*line;
	int			fd;
	t_node		*list;

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
		// printf("line: %s\n", line);
		line = trim(line, '\n');
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
