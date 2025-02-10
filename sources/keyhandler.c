
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
	t_object	*camera;
	t_vector	to_camera;

	if (selected == NULL)
		return (failure("No object selected"));
	camera = get_object(objarr, CAMERA);
	to_camera = normalize_vector(v_sub(camera->location, selected->location));
	if (mlx_data.key == MLX_KEY_KP_9)
		delta = v_mul(-1, to_camera); // away from camera
	else if (mlx_data.key == MLX_KEY_KP_1)
		delta = to_camera; // towards camera
	else if (mlx_data.key == MLX_KEY_KP_8)
		delta = camera->info.v; // up
	else if (mlx_data.key == MLX_KEY_KP_2)
		delta = v_mul(-1, camera->info.v); // down
	else if (mlx_data.key == MLX_KEY_KP_6)
		delta = camera->info.u; // right
	else if (mlx_data.key == MLX_KEY_KP_4)
		delta = v_mul(-1, camera->info.u); // left
	else
		return (FAILURE);
	translate_object(selected, delta, objarr);
	print_vector(selected->location);
	return (SUCCESS);
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
		if (translate(mlx_data, data->ui->selected, data->objects) == SUCCESS)
			redraw(data);
		select_object_by_index(mlx_data, data);
	}
}
