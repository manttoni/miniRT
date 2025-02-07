#include "../includes/minirt.h"

void redraw(t_data *data)
{
	raycast(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}