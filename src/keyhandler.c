#include "../inc/minirt.h"

int	handle_close(void *param)
{
	free_data(param);
	exit(0);
}

int	handle_key(int key, t_data *data)
{
	if (key == ESCAPE_KEY)
	{
		free_data(data);
		exit(0);
	}
	if (key == W)
	{
		data->alpha += 0.01;
		raycast(data);
		mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0,0);
	}
	return (0);
}
