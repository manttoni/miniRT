#include "../includes/minirt.h"

int	cast_ray(t_vector d, t_data *data)
{
	double	distance;
	int		color;
	t_node	*current;
	double	closest_dist;
	int		closest_color;

	closest_dist = DBL_MAX;
	closest_color = BACKGROUND_COLOR;
	distance = 0;
	current = data->objects;
	while (current)
	{
		color = sphere_collision(d, current->data, &distance);
		if (distance < closest_dist && color != BACKGROUND_COLOR)
			closest_color = color;
		current = current->next;
	}
	return (closest_color);
}

void	raycast(t_data *data)
{
	int		x;
	int		y;
	int		pixel_color;

	y = -Y / 2;
	while (y < Y / 2)
	{
		x = -X / 2;
		while (x < X / 2)
		{
			pixel_color = cast_ray(normalize_vector(vector(x, y, -data->image->focal_len)), data);
			color_pixel(data, pixel_color, x, y);
			x++;
		}
		y++;
	}
}
