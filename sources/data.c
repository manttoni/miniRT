#include "../includes/minirt.h"

static int	mlx_and_image(t_data *data)
{
	data->mlx = mlx_init(X, Y, "miniRT", true);
	if (data->mlx == NULL)
	{
		error_msg(data);
		return (failure("MLX initialization failed"));
	}
	data->image = mlx_new_image(data->mlx, X, Y);
	if (data->image == NULL)
	{
		error_msg(data);
		return (failure("image initialization failed"));
	}
	return (SUCCESS);
}

int	data_mallocs(t_data *data, char *file)
{
	if (data == NULL)
		return (failure("malloc failed"));
	ft_bzero(data, sizeof(t_data));
	ft_bzero(&(data->mouse), sizeof(t_mouse));
	data->file = file;
	data->ambient = malloc(sizeof(t_ambient));
	data->light = malloc(sizeof(t_light));
	if (data->ambient == NULL || data->light == NULL)
		return (failure("malloc failed"));
	data->camera = malloc(sizeof(t_object) * 3);
	if (data->camera == NULL)
		return (failure("malloc failed"));
	data->light->light = data->camera + 1;
	data->ambient->ambient = data->camera + 2;
	data->camera->type = NONE;
	data->light->light->type = NONE;
	data->ambient->ambient->type = NONE;
	return (SUCCESS);
}

t_data	*init_data(char *file)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data_mallocs(data, file) == FAILURE
		|| read_objects(data) == FAILURE
		|| mlx_and_image(data) == FAILURE)
	{
		free_data(data);
		return (NULL);
	}
	print_objects(data);
	select_object(data->camera, data);
	return (data);
}

void	free_data(t_data *data)
{
	if (data == NULL)
		return ;
	free_objarr(data->objects);
	free(data->light);
	free(data->ambient);
	free(data->camera);
	free(data);
}
