#include "../inc/minirt.h"

t_data	*init_data(int x, int y)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->x = x;
	data->y = y;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->x, data->y, "raytracing test");
	data->image = init_image(data);
	data->objects = malloc(sizeof(t_node));
	return (data);
}

void	free_data(t_data *data)
{
	free_list(data->objects);
	mlx_destroy_image(data->mlx, data->image->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->image);
	free(data->mlx);
	free(data);
}
