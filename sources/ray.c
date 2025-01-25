
#include "../includes/defines.h"
#include "../includes/vector.h"
#include "../includes/object.h"
#include "../includes/ray.h"
#include "../includes/color.h"

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
	return (ray);
}

int	cast_ray(t_ray *ray, t_node *objects, double render_distance)
{
	double	closest_dist;

	while (ray->distance < render_distance)
	{
		closest_dist = closest(ray, objects);
		if (closest_dist < 0.01)
			break ;
		ray->distance += closest_dist;
		ray->location = vector_multiply(ray->distance, ray->direction);
	}
	return ray->distance < render_distance;
}

int	light_obstructed(t_ray *ray, t_node *objects)
{
	t_ray	light_ray;
	t_object *light;

	light_ray = *ray;
	light = get_object(objects, LIGHT);
	light_ray.direction = vector_substract(light->location, light_ray.location);
	light_ray.direction = normalize_vector(light_ray.direction);
	light_ray.distance = 0;
	light_ray.location = vector_sum(light_ray.location, light_ray.direction);
	light_ray.location = vector_sum(light_ray.location, light_ray.direction);
	return (cast_ray(&light_ray, objects, vector_dist(light_ray.location, light->location)));
}

void	raycast(t_data *data)
{
	int	x;
	int	y;
	t_ray ray;
	t_object *camera;

	camera = get_object(data->objects, CAMERA);
	y = 0;
	while (y < Y)
	{
		x = 0;
		while (x < X)
		{
			ray = get_ray(camera, x, y);
			if (cast_ray(&ray, data->objects, RENDER_DISTANCE) == 1)
				if (light_obstructed(&ray, data->objects) == 0)
					color_pixel(data->image, ray.color, x, y);
			x++;
		}
		printf("%d%%\r", (((y * X) + x) * 100) / (Y * X));
		y++;
	}
	printf("Raycasting completed\n");
}
/*
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
*/
/*
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
}*/