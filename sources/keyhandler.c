
#include "../includes/minirt.h"

/* select an object by its index in the array, visible in terminal. only 0-9 */
static void	select_object_by_index(mlx_key_data_t mlx_data, t_data *data)
{
	if (mlx_data.key == MLX_KEY_C)
	{
		data->ui->selected = get_object(data->objects, CAMERA);
		printf("Object selected: \n");
    	print_object(data->ui->selected);
	}
	if (mlx_data.key == MLX_KEY_L)
	{
		data->ui->selected = get_object(data->objects, LIGHT);
		printf("Object selected: \n");
    	print_object(data->ui->selected);
	}
	if (mlx_data.key == MLX_KEY_A)
	{
		data->ui->selected = get_object(data->objects, AMBIENT);
		printf("Object selected: \n");
    	print_object(data->ui->selected);
	}
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
		delta = camera->orientation; // to camera direction
	else if (mlx_data.key == MLX_KEY_KP_1)
		delta = v_mul(-1, camera->orientation); // to opposite camera direction
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

static int	resize_object(mlx_key_data_t mlx_data, t_object *selected)
{
	if (selected->type == SPHERE || selected->type == CYLINDER)
	{
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
	}
	return (FAILURE);
}

static int	rotate(mlx_key_data_t mlx_data, t_object *selected, t_objarr *objarr)
{
	t_object	*camera;
	float		delta;
	delta = 0.1;
	camera = get_object(objarr, CAMERA);
	if (mlx_data.key == MLX_KEY_LEFT)
		selected->orientation = rotate_vector_x(selected->orientation, delta);
	else if (mlx_data.key == MLX_KEY_RIGHT)
		selected->orientation = rotate_vector_x(selected->orientation, -delta);
	else if (mlx_data.key == MLX_KEY_UP)
		selected->orientation = rotate_vector_y(selected->orientation, delta);
	else if (mlx_data.key == MLX_KEY_DOWN)
		selected->orientation = rotate_vector_y(selected->orientation, -delta);
	else if (mlx_data.key == MLX_KEY_DELETE)
		selected->orientation = rotate_vector_z(selected->orientation, delta);
	else if (mlx_data.key == MLX_KEY_PAGE_DOWN)
		selected->orientation = rotate_vector_z(selected->orientation, -delta);
	else
		return (FAILURE);
	set_precalculations(objarr);
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
			print_objects(data->objects);
		if (mlx_data.key == MLX_KEY_COMMA)
			print_help();
		if (mlx_data.key == MLX_KEY_R)
			reset_scene(data);
		if (translate(mlx_data, data->ui->selected, data->objects) == SUCCESS)
			redraw(data);
		if (rotate(mlx_data, data->ui->selected, data->objects) == SUCCESS)
			redraw(data);
		if (resize_object(mlx_data, data->ui->selected) == SUCCESS)
			redraw(data);
		select_object_by_index(mlx_data, data);
	}
}
