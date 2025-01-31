#include "../includes/minirt.h"

t_objarr	*read_objects(char *file)
{
	char		*line;
	int			fd;
	t_objarr	*objarr;

	fd = open(file, O_RDONLY);
	objarr = init_objarr(4);
	if (objarr == NULL || fd < 0)
	{
		if (fd > 2)
			close(fd);
		free_objarr(objarr);
		return (NULL);
	}
	line = trim_newline(get_next_line(fd));
	while (line)
	{
		if (*line != '\0' && *line != '#' && add(objarr, parse_object(line)) == FAILURE)
		{
			free_objarr(objarr);
			free(line);
			close(fd);
			return (NULL);
		}
		free(line);
		line = trim_newline(get_next_line(fd));
	}
	close(fd);
	return (objarr);
}

