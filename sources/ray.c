
#include "../includes/minirt.h"
#include "../includes/vector.h"
#include "../includes/object.h"
#include "../includes/ray.h"


int cast_ray(t_ray *ray, t_node *objects)
{
	t_node	*current;
	t_object *object;

	current = objects;
	while (current)
	{
		object = (t_object *)current->data;
		if (object->collision != NULL)
			object->collision(ray, object);
		current = current->next;
	}
	return (0);
}

/*
	t_vector u, v
		perpendicular vectors that define the image plane
*/
t_ray	get_ray(t_object *camera, int x, int y)
{
	t_ray		ray;
	t_vector	u;
	t_vector	v;

	u = vector(-camera->orientation.y, camera->orientation.x, 0);
	v = cross_product(camera->orientation, u);
	ray.start = camera->location;
	ray.direction = vector_sum(camera->location, vector_multiply(camera->view_distance, camera->orientation)); // image center
	vector_sum(ray.direction, vector_multiply((-X / 2 + x + 0.5), u));
	vector_sum(ray.direction, vector_multiply((-Y / 2 + y + 0.5), v));
	normalize_vector(ray.direction);
	ray.distance = DBL_MAX;
	ray.color = 0;
	return (ray);
}

void	raycast(t_data *data)
{
	int			x;
	int			y;
	// int	pixel_color;
	t_object	*camera;
	t_ray		ray;

	camera = get_camera(data->objects);
	y = 0;
	while (y < Y)
	{
		x = 0;
		while (x < X)
		{
			ray = get_ray(camera, x, y);
			cast_ray(&ray, data->objects);
			color_pixel(data->image, ray.color, x, y);
			x++;
		}
		y++;
	}
}
