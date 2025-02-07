
#include "../includes/minirt.h"

// int	handle_close(void *param)
// {
// 	free_data(param);
// 	exit(0);
// }


void	keypress(mlx_key_data_t mlx_data, void *param)
{
	t_data	*data;
	static t_vector axis;
	t_object		*arr;

	data = (t_data *)param;
	arr = data->objects->arr;
	if (mlx_data.action == MLX_PRESS)
	{
		if (mlx_data.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(data->mlx);
			return ;
		}
		if (mlx_data.key == MLX_KEY_X)
		{
			axis = vector(1, 0, 0);
			printf("Move X\n");
		}
		if (mlx_data.key == MLX_KEY_Y)
		{
			axis = vector(0, 1, 0);
			printf("Move Y\n");
		}
		if (mlx_data.key == MLX_KEY_Z)
		{
			axis = vector(0, 0, 1);
			printf("Move Z\n");
		}
		if (mlx_data.key == MLX_KEY_KP_ADD)
		{
			data->ui->selected->location = v_sum(data->ui->selected->location, axis);
			print_vector(data->ui->selected->location);
			redraw(data);
		}
		if (mlx_data.key == MLX_KEY_KP_SUBTRACT)
		{
			data->ui->selected->location = v_sub(data->ui->selected->location, axis);
			print_vector(data->ui->selected->location);
			redraw(data);
		}
	}
}
