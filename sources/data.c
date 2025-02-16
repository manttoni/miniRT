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

int data_mallocs(t_data *data)
{
	data->ambient = malloc(sizeof(t_ambient));
	data->light = malloc(sizeof(t_light));
	if (data->ambient == NULL || data->light == NULL)
		return (FAILURE);
	data->camera = malloc(sizeof(t_object) * 3);
	if (data->camera == NULL)
		return (FAILURE);
	data->light->light = data->camera + 1;
	data->ambient->ambient = data->camera + 2;
	return (SUCCESS);
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
	if (data_mallocs(data) == FAILURE || read_objects(data) == FAILURE)
	{
		error_msg(data);
		free(data);
		return (NULL);
	}
	if (mlx_and_image(data))
		return (NULL);
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
