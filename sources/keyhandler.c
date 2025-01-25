
#include "../includes/minirt.h"

int	handle_close(void *param)
{
	free_data(param);
	exit(0);
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
	}
}
