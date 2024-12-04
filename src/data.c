#include "../inc/minirt.h"

t_data	*init_data(int x, int y, char *file)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	ft_bzero(data, sizeof(t_data));
	data->x = x;
	data->y = y;
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (NULL);
	data->win = mlx_new_window(data->mlx, data->x, data->y, "raytracing test");
	data->image = init_image(data);
	data->objects = read_objects(char *file);
	if (data->win == NULL || data->image == NULL || data->objects == NULL)
		return (NULL);
	return (data);
}

void	free_data(t_data *data)
{
	if (data == NULL)
		return ;
	free_list(data->objects);
	free(data->image);
	if (data->mlx)
	{
		mlx_destroy_image(data->mlx, data->image->img);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data);
}
