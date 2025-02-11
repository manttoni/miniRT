
#include "../includes/minirt.h"

static int	mlx_and_image(t_data *data)
{
	data->mlx = mlx_init(X, Y, "miniRT", true);
	if (data->mlx == NULL)
	{
		error_msg(data);
		return (1);
	}
	data->image = mlx_new_image(data->mlx, X, Y);
	if (data->image == NULL)
	{
		error_msg(data);
		return (1);
	}
	return (0);
}

t_data	*init_data(char *file)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		error_msg(data);
		return (NULL);
	}
	ft_bzero(data, sizeof(t_data));
	data->mouse.left = 0;
	data->mouse.right = 0;
	data->file = file;
	data->light = malloc(sizeof(t_light));
	data->light->light = malloc(sizeof(t_object));
	data->camera = malloc(sizeof(t_object));
	data->light->ambient = malloc(sizeof(t_object));
	if (read_objects(data, file) == FAILURE)
	{
		error_msg(data);
		free(data);
		return (NULL);
	}
	if (mlx_and_image(data))
		return (NULL);
	data->selected = data->camera;
	return (data);
}

void	free_data(t_data *data)
{
	if (data == NULL)
		return ;
	free_objarr(data->objects);
	free(data);
}
