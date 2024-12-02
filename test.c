#include "inc/minirt.h"

t_camera	*init_camera(void)
{
	t_camera *camera = malloc(sizeof(t_camera));
	if (camera == NULL)
		return (NULL);
	camera->location = (t_vector){0,0,0};
	camera->direction = (t_vector){0,1,0};
	camera->focal_len = 100;
	return camera;
}

int main(void)
{
	t_data	*data = init_data(1000, 750);
	if (data == NULL)
		return (1);
	data->camera = init_camera();
	if (data->camera == NULL)
	{
		free_data(data);
		return (1);
	}
	t_sphere *sphere = create_sphere(vector(0, 0, -200), 250, 255 << 16 | 255 << 8 | 255);
	t_node *node = create_node(sphere);
	data->objects = NULL;
	add_node(&(data->objects), node);
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
	mlx_loop(data->mlx);
	return (0);
}
