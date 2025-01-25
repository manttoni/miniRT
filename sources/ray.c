
#include "../includes/defines.h"
#include "../includes/vector.h"
#include "../includes/object.h"
#include "../includes/ray.h"
#include "../includes/color.h"

t_ray	get_ray(t_object *camera, int x, int y)
{
	t_ray		ray;

	ray = camera->info.ray;
	ray.direction = vector_sum(ray.direction, vector_multiply((-X / 2 + x + 0.5), camera->info.u));
	ray.direction = vector_sum(ray.direction, vector_multiply((-Y / 2 + y + 0.5), camera->info.v));
	ray.direction = normalize_vector(ray.direction);
	return (ray);
}

int	cast_ray(t_ray *ray, t_node *objects, double render_distance)
{
	double	closest_dist;
	double	close_enough;

	close_enough = 0.001;
	while (ray->distance < render_distance)
	{
		closest_dist = closest(ray, objects);
		if (closest_dist < close_enough)
			return 1 ;
		ray->distance += closest_dist;
		ray->location = vector_sum(ray->location, vector_multiply(closest_dist, ray->direction));
	}
	return 0;
}

int	light_obstructed(t_ray *ray, t_node *objects)
{
	t_ray	light_ray;
	t_object *light;
	double self_collision_avoid = 10;

	light_ray = *ray;
	light = get_object(objects, LIGHT);
	light_ray.direction = vector_substract(light->location, light_ray.location);
	light_ray.direction = normalize_vector(light_ray.direction);
	light_ray.distance = self_collision_avoid;
	light_ray.location = vector_sum(light_ray.location, vector_multiply(self_collision_avoid, light_ray.direction));
	return (cast_ray(&light_ray, objects, vector_dist(light_ray.location, light->location) - self_collision_avoid));
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
			{
				if (light_obstructed(&ray, data->objects) == 0)
				{
					color_pixel(data->image, ray.color, x, y);
				}
				else
					color_pixel(data->image, BACKGROUND_COLOR, x, y);
			}
			x++;
		}
		printf("%d%%\r", (((y * X) + x) * 100) / (Y * X));
		y++;
	}
	printf("Raycasting completed\n");
}