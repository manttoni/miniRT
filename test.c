#include "inc/minirt.h"

t_camera	*init_camera(void)
{
	t_camera *camera = malloc(sizeof(t_camera));
	if (camera == NULL)
		return (NULL);
	camera->location = (t_vector){0,0,0};
	camera->direction = (t_vector){0,1,0};
	camera->focal_len = 1000;
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
	data->objects = NULL;
	add_node(&(data->objects), create_node(create_sphere(vector(0, 0, -100), 25, BLUE)));
	add_node(&(data->objects), create_node(create_sphere(vector(250, 0, -1200), 250, SALMON)));
	add_node(&(data->objects), create_node(create_sphere(vector(0, 350, -1300), 250, YELLOW)));
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
	mlx_loop(data->mlx);
	return (0);
}
