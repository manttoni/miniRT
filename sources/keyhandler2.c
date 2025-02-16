#include "../includes/minirt.h"

int	resize_object(mlx_key_data_t mlx_data, t_object *selected)
{
	double	delta;

	delta = 1;
	if (mlx_data.key == MLX_KEY_KP_ADD && selected->diameter + delta < DBL_MAX)
	{
		selected->diameter += delta;
		return (SUCCESS);
	}
	else if (mlx_data.key == MLX_KEY_KP_SUBTRACT
		&& selected->diameter - delta > 0)
	{
		selected->diameter -= delta;
		return (SUCCESS);
	}
	if (mlx_data.key == MLX_KEY_PAGE_DOWN && selected->height - delta > 0)
	{
		selected->height -= delta;
		return (SUCCESS);
	}
	if (mlx_data.key == MLX_KEY_PAGE_UP && selected->height + delta < DBL_MAX)
	{
		selected->height += delta;
		return (SUCCESS);
	}
	return (FAILURE);
}

int	adjust_brightness(mlx_key_data_t mlx_data, t_object *selected)
{
	double	delta;

	delta = 0.1;
	if (mlx_data.key == MLX_KEY_KP_ADD
		&& selected->brightness + delta <= 1)
		selected->brightness += delta;
	else if (mlx_data.key == MLX_KEY_KP_SUBTRACT
		&& selected->brightness - delta >= 0)
		selected->brightness -= delta;
	else
		return (FAILURE);
	return (SUCCESS);
}

int	change_fov(mlx_key_data_t mlx_data, t_object *selected)
{
	double	delta;

	delta = 10;
	if (mlx_data.key == MLX_KEY_KP_ADD && selected->fov + delta <= 180)
		selected->fov += delta;
	else if (mlx_data.key == MLX_KEY_KP_SUBTRACT && selected->fov - delta >= 0)
		selected->fov -= delta;
	else
		return (FAILURE);
	return (SUCCESS);
}
