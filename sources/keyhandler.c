
#include "../includes/minirt.h"

int	handle_close(void *param)
{
	free_data(param);
	exit(0);
}

// void	handle_key(int key, t_data *data)
void	keypress(mlx_key_data_t mlx_data, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	// if (key == ESCAPE_KEY)
	// {
	// 	free_data(data);
	// 	exit(0);
	// }
	if (mlx_data.action == MLX_PRESS)
	{
		if (mlx_data.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(data->mlx);
			return ;
		}
	}
}
