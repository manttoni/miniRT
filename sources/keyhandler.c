
#include "../includes/minirt.h"

static void	select_object_by_index(mlx_key_data_t mlx_data, t_data *data)
{
	if (mlx_data.key >= MLX_KEY_0 && mlx_data.key <= MLX_KEY_9)
		select_object(&data->objects->arr[mlx_data.key - MLX_KEY_0], data->ui);
}

static int	translate(mlx_key_data_t mlx_data, t_object *selected, t_object *camera)
{
	t_vector	delta;

	if (mlx_data.key == MLX_KEY_KP_9)
		delta = vector(0, 0, 1);
	else if (mlx_data.key == MLX_KEY_KP_1)
		delta = vector(0, 0, -1);
	else if (mlx_data.key == MLX_KEY_KP_8)
		delta = vector(0, 1, 0);
	else if (mlx_data.key == MLX_KEY_KP_2)
		delta = vector(0, -1, 0);
	else if (mlx_data.key == MLX_KEY_KP_6)
		delta = vector(1, 0, 0);
	else if (mlx_data.key == MLX_KEY_KP_4)
		delta = vector(-1, 0, 0);
	else
		return (0);
	translate_object(selected, delta, camera);
	print_vector(selected->location);
	return (1);
}

void	keypress(mlx_key_data_t mlx_data, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_data.action == MLX_PRESS)
	{
		if (mlx_data.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(data->mlx);
			return ;
		}
		if (translate(mlx_data, data->ui->selected, get_object(data->objects, CAMERA)) == 1)
			redraw(data);
		select_object_by_index(mlx_data, data);
	}
}
