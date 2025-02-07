
#include "../includes/minirt.h"

int	handle_close(void *param)
{
	free_data(param);
	exit(0);
}

static size_t	select_next_object(size_t selected, t_objarr *objarr)
{
	if (selected == objarr->objects - 1)
		return (0);
	return (selected + 1);
}

static void redraw(t_data *data)
{
	raycast(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}

void	keypress(mlx_key_data_t mlx_data, void *param)
{
	t_data	*data;
	static int		selected;
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
		if (mlx_data.key == MLX_KEY_TAB)
		{
			selected = select_next_object(selected, data->objects);
			print_object(arr[selected]);
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
			arr[selected].location = v_sum(arr[selected].location, axis);
			print_vector(arr[selected].location);
			redraw(data);
		}
		if (mlx_data.key == MLX_KEY_KP_SUBTRACT)
		{
			arr[selected].location = v_sub(arr[selected].location, axis);
			print_vector(arr[selected].location);
			redraw(data);
		}
		if (mlx_data.key == MLX_KEY_ENTER)
			redraw(data);
		
	}
}

void	rt_mouse(void *param)
{
	int32_t	mouse_x;
	int32_t	mouse_y;
	t_data	*data;
	t_vector	new_orientation;
	t_object	*camera;

	data = (t_data *)param;
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(data->mlx, &mouse_x, &mouse_y);
		camera = get_object(data->objects, CAMERA);
		new_orientation = get_ray(camera, mouse_x, mouse_y).direction;
		rotate_object(get_object(data->objects, CAMERA), new_orientation);
		redraw(data);
	}
}