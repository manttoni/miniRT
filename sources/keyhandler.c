
#include "../includes/minirt.h"

/* select an object by its index in the array, visible in terminal. only 0-9 */
static void	select_object_by_index(mlx_key_data_t mlx_data, t_data *data)
{
	if (mlx_data.key >= MLX_KEY_0 && mlx_data.key <= MLX_KEY_9)
		select_object(&data->objects->arr[mlx_data.key - MLX_KEY_0], data->ui);
}

/* checks which key is pressed, creates a vector and translates the object in that direction */
static int	translate(mlx_key_data_t mlx_data, t_object *selected, t_objarr *objarr)
{
	t_vector	delta;

	if (mlx_data.key == MLX_KEY_KP_9)
		delta = vector(0, 0, 1);
	else if (mlx_data.key == MLX_KEY_KP_1)
		delta = vector(0, 0, -1);
	else if (mlx_data.key == MLX_KEY_KP_8)
		delta = vector(0, 1, 0);
	else if (mlx_data.key == MLX_KEY_KP_2)
		delta = vector(0, -1, 0);
	else if (mlx_data.key == MLX_KEY_KP_6)
		delta = vector(1, 0, 0);
	else if (mlx_data.key == MLX_KEY_KP_4)
		delta = vector(-1, 0, 0);
	else
		return (0);
	translate_object(selected, delta, objarr);
	print_vector(selected->location);
	return (1);
}

void	print_help(void)
{
	printf("--------------\n");
	printf("HOME: print objects\n");
	printf("COMMA: this menu\n");
	printf("First select object with numbers or left click\n");
	printf("Movement keys (numpad):\n");
	printf("X: 4 & 6\nY: 8 & 2\nZ: 9 & 1\n");
	printf("Left click rotates camera\n");
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
		if (mlx_data.key == MLX_KEY_HOME)
			print_objects(data->objects);
		if (mlx_data.key == MLX_KEY_COMMA)
			print_help();
		if (translate(mlx_data, data->ui->selected, data->objects) == 1)
			redraw(data);
		select_object_by_index(mlx_data, data);
	}
}
