
#include "../includes/minirt.h"

int	handle_close(void *param)
{
	free_data(param);
	exit(0);
}

static int	select_next_object(int selected, t_object **arr)
{
	if (arr[selected + 1] == NULL)
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
	t_object		**arr;

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
			selected = select_next_object(selected, arr);
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
			arr[selected]->location = v_sum(arr[selected]->location, axis);
			print_vector(arr[selected]->location);
			redraw(data);
		}
		if (mlx_data.key == MLX_KEY_KP_SUBTRACT)
		{
			arr[selected]->location = v_sub(arr[selected]->location, axis);
			print_vector(arr[selected]->location);
			redraw(data);
		}
		if (mlx_data.key == MLX_KEY_ENTER)
			redraw(data);
	}
}
