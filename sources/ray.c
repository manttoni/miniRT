
#include "../includes/minirt.h"
#include "../includes/vector.h"
#include "../includes/object.h"
#include "../includes/ray.h"

int cast_ray(t_ray *ray, t_node *objects)
{
	t_node	*current;
	t_object *object;
	int			has_collision;

	has_collision = 0;
	current = objects;
	while (current)
	{
		object = (t_object *)current->data;
		if (object->collision != NULL)
			if (object->collision(ray, object) == 1)
				has_collision = 1;
		current = current->next;
	}
	return (has_collision);
}

/*
	t_vector u, v
		perpendicular vectors that define the image plane
	t_object *camera
		already has precalculated basic vectors u and v
	camera->info.ray
		precalculated part of the ray
*/
t_ray	get_ray(t_object *camera, int x, int y)
{
	t_ray		ray;

	// method 1
	//ft_memcpy(&ray, &(camera->info.ray), sizeof(t_ray));

	// method 2
	ray = camera->info.ray;

	// method 3
	// ray.start = camera->location;
	// ray.direction = vector_multiply(camera->info.view_distance, camera->orientation);
	// ray.direction = vector_sum(camera->location, ray.direction);

	ray.direction = vector_sum(ray.direction, vector_multiply((-X / 2 + x + 0.5), camera->info.u));
	ray.direction = vector_sum(ray.direction, vector_multiply((-Y / 2 + y + 0.5), camera->info.v));
	ray.direction = normalize_vector(ray.direction);
	//ray.distance = DBL_MAX;
	//ray.color = (0xFF << 24) | (0x00 << 16) | (0x00 << 8) | 0x00; // Opaque black
	return (ray);
}

void	raycast(t_data *data)
{
	int			x;
	int			y;
	t_object	*camera;
	t_object	*light;
	t_ray		ray;

	printf("Raycast started!\n");
	camera = get_object(data->objects, CAMERA);
	light = get_object(data->objects, LIGHT);
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
	printf("Raycasting completed!\n");
}
