#include "../includes/minirt.h"

int cast_ray(t_ray *ray, t_object *objects)
{
	t_node	*current;

	current = objects;
	while (current)
	{
		if (current->collision != NULL)
			current->collision(ray, current);
		current = current->next;
	}
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

	u = vector(-camera->direction.y, camera->direction.x, 0);
	v = cross_product(camera->direction, u);
	ray->start = camera->location;
	ray->direction = vector_sum(camera->location, camera->view_distance); // image center
	ray->direction += vector_multiply((-X / 2 + x + 0.5), u);
	ray->direction += vector_multiply((-Y / 2 + j + 0.5), v);
	normalize_vector(ray->direction);
	return (ray);
}

void	raycast(t_data *data)
{
	int			x;
	int			y;
	int			pixel_color;
	t_object	*camera;

	camera = get_camera(data);
	y = -Y / 2;
	while (y < Y / 2)
	{
		x = -X / 2;
		while (x < X / 2)
		{
			pixel_color = cast_ray(&get_ray(camera, x, y), data);
			color_pixel(data, pixel_color, x, y);
			x++;
		}
		y++;
	}
}
