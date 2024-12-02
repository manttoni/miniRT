#include "../inc/minirt.h"

int	cast_ray(t_vector d, t_data *data)
{
	int		color;
	t_node	*current;

	current = data->objects;
	while (current)
	{
		color = sphere_collision(d, current->data);
		if (color != BACKGROUND_COLOR)
			return (color);
		current = current->next;
	}
	return (BACKGROUND_COLOR);
}

void	raycast(t_data *data)
{
	int		x;
	int		y;
	int		pixel_color;
	float	aspect_ratio = (float)data->x / (float)data->y;

	y = -data->y / 2;
	while (y < data->y / 2)
	{
		x = -data->x / 2;
		while (x < data->x / 2)
		{
			pixel_color = cast_ray(normalize_vector(vector(x, y, -data->camera->focal_len)), data);
			color_pixel(data, pixel_color, x, y);
			x++;
		}
		y++;
	}
}
