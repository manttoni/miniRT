
#include "../includes/minirt.h"

/* select an object by its index in the array, visible in terminal. only 0-9 */
static void	select_object_by_index(mlx_key_data_t mlx_data, t_data *data)
{
	if (mlx_data.key == MLX_KEY_C)
	{
		data->selected = data->camera;
		printf("Object selected: \n");
    	camera_light_ambient(data->camera, NULL, NULL);
	}
	if (mlx_data.key == MLX_KEY_L)
	{
		data->selected = data->light->light;
		printf("Object selected: \n");
    	camera_light_ambient(NULL, data->light->light, NULL);
	}
	if (mlx_data.key == MLX_KEY_A)
	{
		data->selected = data->ambient->ambient;
		printf("Object selected: \n");
    	camera_light_ambient(NULL, NULL, data->ambient->ambient);
	}
	if (mlx_data.key >= MLX_KEY_0 && mlx_data.key <= MLX_KEY_9)
	{
		if (mlx_data.key - MLX_KEY_0 < data->objects->objects)
			select_object(&data->objects->arr[mlx_data.key - MLX_KEY_0], data);
	}
}

/* checks which key is pressed, creates a vector and translates the object in that direction */
static int	translate(mlx_key_data_t mlx_data, t_object *selected, t_data *data)
{
	t_vector	delta;
	t_object	*camera;

	if (selected == NULL)
		return (failure("No object selected"));
	camera = data->camera;
	if (mlx_data.key == MLX_KEY_KP_9)
		delta = camera->orientation; // to camera direction
	else if (mlx_data.key == MLX_KEY_KP_1)
		delta = v_mul(-1, camera->orientation); // to opposite camera direction
	else if (mlx_data.key == MLX_KEY_KP_2)
		delta = data->info.v; // up
	else if (mlx_data.key == MLX_KEY_KP_8)
		delta = v_mul(-1, data->info.v); // down
	else if (mlx_data.key == MLX_KEY_KP_6)
		delta = data->info.u; // right
	else if (mlx_data.key == MLX_KEY_KP_4)
		delta = v_mul(-1, data->info.u); // left
	else
		return (FAILURE);
	translate_object(selected, delta);
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

static int	resize_object(mlx_key_data_t mlx_data, t_object *selected)
{
	double	delta;

	delta = 1;
	if (mlx_data.key == MLX_KEY_KP_ADD)
	{
		selected->diameter += 1;
		if (selected->diameter > DBL_MAX)
			selected->diameter = DBL_MAX;
		return (SUCCESS);
	}
	else if (mlx_data.key == MLX_KEY_KP_SUBTRACT)
	{
		selected->diameter -= 1;
		if (selected->diameter <= 0)
			selected->diameter = 1.0;
		return(SUCCESS);
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

static int	adjust_brightness(mlx_key_data_t mlx_data, t_object *selected)
{
	double	delta;

	delta = 0.1;
	if (mlx_data.key == MLX_KEY_KP_ADD && selected->brightness + delta <= 1)
		selected->brightness += delta;
	else if (mlx_data.key == MLX_KEY_KP_SUBTRACT && selected->brightness - delta >= 0)
		selected->brightness -= delta;
	else
		return (FAILURE);
	return (SUCCESS);
}

static int	change_fov(mlx_key_data_t mlx_data, t_object *selected)
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
	print_vector(selected->orientation);
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
