#include "inc/minirt.h"

int main(void)
{
	t_data	*data = init_data(1000, 750);
	if (data == NULL)
	{
		free_data(data);
		return (1);
	}
	raycast(data);
	mlx_key_hook(data->win, handle_key, data);
	mlx_hook(data->win, 17, 0, handle_close, data);
	mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
	mlx_loop(data->mlx);
	return (0);
}
