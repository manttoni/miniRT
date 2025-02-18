#include "../includes/minirt.h"

void	redraw(t_data *data)
{
	set_precalculations(data);
	raycast(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}

void	reset_scene(t_data *data)
{
	free_objarr(data->objects);
	data->camera->type = NONE;
	data->light->light->type = NONE;
	data->ambient->ambient->type = NONE;
	read_objects(data);
	data->selected = data->camera;
	printf("Scene resetted\n");
	redraw(data);
}
