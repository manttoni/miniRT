#include "../includes/minirt.h"

/* Check if objarr has exactly one of A, C and L */
static t_objarr	*check_uniques(t_objarr *objarr)
{
	size_t	i;
	size_t	types[3];

	i = 0;
	ft_memset(types, 0, 3 * sizeof(size_t));
	while (i < objarr->objects)
	{
		if (objarr->arr[i].type == AMBIENT)
			types[0]++;
		else if (objarr->arr[i].type == CAMERA)
			types[1]++;
		else if (objarr->arr[i].type == LIGHT)
			types[2]++;
		i++;
	}
	if (types[0] * types[1] * types[2] == 1 && objarr->objects >= 4)
		return (objarr);
	free_objarr(objarr);
	failure("Needs to have LIGHT, CAMERA, AMBIENT and at least one OBJECT");
	return (NULL);
}

/* Calculates all precalculations */
void	set_precalculations(t_objarr *objarr)
{
	size_t	i;
	t_object	*camera;

	i = 0;
	camera = get_object(objarr, CAMERA);
	camera->info = image_plane(camera);
	while (i < objarr->objects)
	{
		if (objarr->arr[i].type == PLANE)
			precalculate_plane(&objarr->arr[i], camera);
		i++;
	}
}

static int	error_check(int fd, t_objarr *objarr)
{
	if (objarr == NULL || fd < 0)
	{
		if (fd > 2)
			close(fd);
		free_objarr(objarr);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_objarr	*read_objects(char *file)
{
	char		*line;
	int			fd;
	t_objarr	*objarr;

	fd = open(file, O_RDONLY);
	objarr = init_objarr(4);
	if (error_check(fd, objarr) == FAILURE)
		return (NULL);
	line = trim_newline(get_next_line(fd));
	while (line)
	{
		if (*line != '\0' && *line != '#' && add_object(objarr, line) == FAILURE)
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
	set_precalculations(objarr);
	return (check_uniques(objarr));
}
