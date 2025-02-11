#include "../includes/minirt.h"

/* Check if objarr has exactly one of A, C and L 
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
*/
/* Calculates all precalculations */
void	set_precalculations(t_data  *data)
{
	size_t	i;

	i = 0;
	data->info = image_plane(data->camera);
	while (i < data->objects->objects)
	{
		if (data->objects->arr[i].type == PLANE)
			precalculate_plane(&data->objects->arr[i], data->info);
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

int	read_objects(t_data *data, char *file)
{
	char		*line;
	int			fd;
	t_objarr	*objarr;

	fd = open(file, O_RDONLY);
	objarr = init_objarr(4);
	if (error_check(fd, objarr) == FAILURE)
		return (FAILURE);
	data->objects = objarr;
	line = trim_newline(get_next_line(fd));
	while (line)
	{
		if (*line != '\0' && *line != '#' && add_object(data, line) == FAILURE)
		{
			free_objarr(objarr);
			free(line);
			close(fd);
			return (FAILURE);
		}
		free(line);
		line = trim_newline(get_next_line(fd));
	}
	close(fd);
	set_precalculations(data);
	return (SUCCESS);
}
