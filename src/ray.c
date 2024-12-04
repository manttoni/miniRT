#include "../inc/minirt.h"

int	cast_ray(t_vector d, t_data *data, t_vector light)
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
		color = sphere_collision(d, current->data, &distance, light);
		if (distance < closest_dist && color != BACKGROUND_COLOR)
			closest_color = color;
		current = current->next;
	}
	return (closest_color);
}

void	transform(t_data *data)
{
	t_object	*object;
	t_node		*olist;

	olist = data->objects;
	while (olist)
	{
		object = (t_object *) olist->data;
		if (object->type == CAMERA || object->type == LIGHT)
		{
			olist = olist->next;
			continue;
		}
		object->location = multi_matrix(object->location, transformation(data->alpha, data->beta, data->gamma));
		olist = olist->next;
	}
}

t_object	*get_light(t_node *objects)
{
	t_object *object;

	while (objects)
	{
		object = (t_object *) objects->data;
		if (object->type == LIGHT)
			return (object);
		objects = objects->next;
	}
	return (NULL);
}

void	raycast(t_data *data)
{
	int			x;
	int			y;
	int			pixel_color;
	float		aspect_ratio = (float)data->x / (float)data->y;
	t_vector	co;
	t_object	*lio = get_light(data->objects);
	t_vector	light = lio->location;

	transform(data);
	co = get_camera(data->objects)->orientation;
	y = -data->y / 2;
	while (y < data->y / 2)
	{
		x = -data->x / 2;
		while (x < data->x / 2)
		{
			pixel_color = cast_ray(normalize_vector(vector(x, y, -data->image->focal_len)), data, light);
			color_pixel(data, pixel_color, x, y);
			x++;
		}
		y++;
	}
}
