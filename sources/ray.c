
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

int	cast_ray(t_ray *ray, t_node *objects)
{
	double	closest_dist;

	while (ray->distance < RENDER_DISTANCE)
	{
		closest_dist = closest(ray, objects);
		if (closest_dist > 1.0)
		{
			ray->distance += closest_dist;
			ray->location = vector_multiply(ray->distance, ray->direction);
			continue ;
		}
		break;
	}
	return 1;
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
			cast_ray(&ray, data->objects);
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