#include "../includes/minirt.h"

/* select an object by its index in the array, visible in terminal. only 0-9 */
static void	select_object_by_index(mlx_key_data_t mlx_data, t_data *data)
{
	if (mlx_data.key == MLX_KEY_C)
		select_object(data->camera, data);
	if (mlx_data.key == MLX_KEY_L)
		select_object(data->light->light, data);
	if (mlx_data.key == MLX_KEY_A)
		select_object(data->ambient->ambient, data);
	if (mlx_data.key >= MLX_KEY_0 && mlx_data.key <= MLX_KEY_9)
	{
		if (mlx_data.key - MLX_KEY_0 < data->objects->objects)
			select_object(&data->objects->arr[mlx_data.key - MLX_KEY_0], data);
	}
}

/* checks which key is pressed, creates a vector 
and translates the object in that direction */
static int	translate(mlx_key_data_t mlx_data, t_object *selected, t_data *data)
{
	t_vector	delta;
	t_object	*camera;

	if (selected == NULL)
		return (failure("No object selected"));
	camera = data->camera;
	if (mlx_data.key == MLX_KEY_KP_9)
		delta = camera->orientation;
	else if (mlx_data.key == MLX_KEY_KP_1)
		delta = v_mul(-1, camera->orientation);
	else if (mlx_data.key == MLX_KEY_KP_2)
		delta = data->info.v;
	else if (mlx_data.key == MLX_KEY_KP_8)
		delta = v_mul(-1, data->info.v);
	else if (mlx_data.key == MLX_KEY_KP_6)
		delta = data->info.u;
	else if (mlx_data.key == MLX_KEY_KP_4)
		delta = v_mul(-1, data->info.u);
	else
		return (FAILURE);
	translate_object(selected, delta);
	return (SUCCESS);
}

static int	change_value(mlx_key_data_t mlx_data, t_object *selected)
{
	if (selected->type == SPHERE || selected->type == CYLINDER)
		return (resize_object(mlx_data, selected));
	if (selected->type == LIGHT || selected->type == AMBIENT)
		return (adjust_brightness(mlx_data, selected));
	if (selected->type == CAMERA)
		return (change_fov(mlx_data, selected));
	return (FAILURE);
}

static int	rotate(mlx_key_data_t mlx_data, t_object *selected, t_data *data)
{
	float		d;

	d = 0.1;
	if (mlx_data.key == MLX_KEY_LEFT)
		rotate_vector(&(selected->orientation), data->info.v, -d);
	else if (mlx_data.key == MLX_KEY_RIGHT)
		rotate_vector(&(selected->orientation), data->info.v, d);
	else if (mlx_data.key == MLX_KEY_UP)
		rotate_vector(&(selected->orientation), data->info.u, d);
	else if (mlx_data.key == MLX_KEY_DOWN)
		rotate_vector(&(selected->orientation), data->info.u, -d);
	else
		return (FAILURE);
	return (SUCCESS);
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
			print_objects(data);
		if (mlx_data.key == MLX_KEY_COMMA)
			print_help();
		if (mlx_data.key == MLX_KEY_R)
			reset_scene(data);
		if (translate(mlx_data, data->selected, data) == SUCCESS)
			redraw(data);
		if (rotate(mlx_data, data->selected, data) == SUCCESS)
			redraw(data);
		if (change_value(mlx_data, data->selected) == SUCCESS)
			redraw(data);
		select_object_by_index(mlx_data, data);
	}
}
