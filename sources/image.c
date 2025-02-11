#include "../includes/minirt.h"

void redraw(t_data *data)
{
	printf("Sphere diameter: %f\n", data->objects->arr[4].diameter);
	raycast(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}

void	reset_scene(t_data *data)
{
	free_objarr(data->objects);
	data->objects = init_objarr(4);
	data->objects = read_objects(data, data->file);
	data->selected = get_object(data->objects, CAMERA);
	printf("Scene resetted\n");
	redraw(data);
}
