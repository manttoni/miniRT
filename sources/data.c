#include "../includes/minirt.h"

t_data	*init_data(char *file)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		printf("data struct malloc fail\n");
		return (NULL);
	}
	ft_bzero(data, sizeof(t_data));
	data->objects = read_objects(file);
	data->x = X;
	data->y = Y;
	data->mlx = mlx_init(X, Y, "miniRT", true);
	if (data->mlx == NULL)
	{
		printf("mlx init fail\n");
		return (NULL);
	}
	// data->win = mlx_new_window(data->mlx, data->x, data->y, "raytracing test");
	data->image = init_image(data);
	if (data->image == NULL || data->objects == NULL)
	{
		printf("data->image: %p data->objects: %p\n", data->image, data->objects);
		return (NULL);
	}
	return (data);
}

void	free_data(t_data *data)
{
	if (data == NULL)
		return ;
	free_list(data->objects);
	if (data->mlx)
	{
		// mlx_destroy_image(data->mlx, data->image->img);
		// mlx_destroy_window(data->mlx, data->win);
		// mlx_destroy_display(data->mlx);
		mlx_terminate(data->mlx);
		free(data->mlx);
	}
	free(data->image);
	free(data);
}
