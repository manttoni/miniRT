#include "../includes/minirt.h"

/* Rotates camera to look at the cursor*/
void left_click(t_data *data)
{
	t_vector new_orientation;

	new_orientation = get_ray(data->info, data->mouse.x, data->mouse.y).direction;
	rotate_object(data->camera, new_orientation);
	redraw(data);
}

/* Selects an object at the cursor*/
void right_click(t_data *data)
{
	t_ray ray;

	ray = get_ray(data->info, data->mouse.x, data->mouse.y);
	if (cast_ray(&ray, data->objects) == 1)
	{
		if (data->selected != ray.object)
			select_object(ray.object, data);
	}
}

/* mouse.left and mouse.right checks prevent the program from executing the functions every frame */
void	rt_mouse(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_get_mouse_pos(data->mlx, &(data->mouse.x), &(data->mouse.y));
	data->mouse.x *= (double)X / data->mlx->width;
	data->mouse.y *= (double)Y / data->mlx->height;
	// printf("Window size: %d %d\n", data->mlx->width, data->mlx->height);
	// printf("Mouse %d %d\n", data->mouse.x, data->mouse.y);
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT) && !data->mouse.left)
	{
		data->mouse.left = 1;
		left_click(data);
	}
	else if (!mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
		data->mouse.left = 0;

	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_RIGHT) && !data->mouse.right)
	{
		data->mouse.right = 1;
		right_click(data);
	}
	else if (!mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_RIGHT))
		data->mouse.right = 0;
}
