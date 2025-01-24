
#include "../includes/minirt.h"

int	handle_close(void *param)
{
	free_data(param);
	exit(0);
}


/*void move_camera(mlx_key_data_t mlx_data, t_data *data)
{
	t_object	*camera;
	double		speed;

	speed = 0.4;
	camera = get_object(data->objects, CAMERA);
	if (mlx_data.key == MLX_KEY_RIGHT)
		camera->orientation.y += speed;
	if (mlx_data.key == MLX_KEY_LEFT)
		camera->orientation.y -= speed;
	if (mlx_data.key == MLX_KEY_UP)
		camera->orientation.z += speed;
	if (mlx_data.key == MLX_KEY_DOWN)
		camera->orientation.z -= speed;
	camera->orientation = normalize_vector(camera->orientation);
	camera->info = image_plane(camera);
	raycast(data);
	mlx_image_to_window(data->mlx, data->image->img , 0, 0);
}*/

// void	handle_key(int key, t_data *data)
void	keypress(mlx_key_data_t mlx_data, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	// if (key == ESCAPE_KEY)
	// {
	// 	free_data(data);
	// 	exit(0);
	// }
	if (mlx_data.action == MLX_PRESS)
	{
		if (mlx_data.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(data->mlx);
			return ;
		}
		//move_camera(mlx_data, data);
	}
}
