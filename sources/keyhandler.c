
#include "../includes/minirt.h"

int	handle_close(void *param)
{
	free_data(param);
	exit(0);
}

static t_object *select_next_object(t_object *selected, t_object *objects)
{
	t_object	*current;

	if (selected == NULL)
		return (objects);
	current = objects;
	while (current)
	{
		if (current == selected)
		{
			if (current->next == NULL)
				return (objects);
			else
				return (current->next);
		}
		current = current->next;
	}
	return (NULL);
}

static void redraw(t_data *data)
{
	raycast(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}

void	keypress(mlx_key_data_t mlx_data, void *param)
{
	t_data	*data;
	static t_object *selected;
	static t_vector axis;

	data = (t_data *)param;
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
			print_object(selected);
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
			selected->location = v_sum(selected->location, axis);
			print_vector(selected->location);
		}
		if (mlx_data.key == MLX_KEY_KP_SUBTRACT)
		{
			selected->location = v_sub(selected->location, axis);
			print_vector(selected->location);
		}
		if (mlx_data.key == MLX_KEY_ENTER)
			redraw(data);
	}
}
