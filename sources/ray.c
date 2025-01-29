#include "../includes/minirt.h"

/*	Returns a ray that is pointing towards pixel(x,y) of the image plane
	Camera holds precalculated data
		Basic vectors (u and v) of the image plane. Used for finding pixels
		All rays share some information like starting point and general direction
		aka camera direction	*/
t_ray	get_ray(t_object *camera, int x, int y)
{
	t_ray		ray;

	// precalculated part of the ray
	// ray location is the camera
	// ray direction is the center of the image plane
	ray = camera->info.ray;

	// this tilts the ray direction towards a pixel on the image plane
	ray.direction = v_sum(ray.direction, v_mul((-X / 2 + x + 0.5), camera->info.u));
	ray.direction = v_sum(ray.direction, v_mul((-Y / 2 + y + 0.5), camera->info.v));
	ray.direction = normalize_vector(ray.direction);
	return (ray);
}

/*	Calculates collisions based on distance to the closest object
	If it is less than close_enough, it is a collision
	Otherwise moves ray to its direction by that amount	*/
int	cast_ray(t_ray *ray, t_object *objects, double render_distance)
{
	double	closest_dist;
	double	close_enough;
	int		i;

	i = 0;
	close_enough = 0.001;
	while (ray->distance < render_distance)
	{
		closest_dist = closest(ray, objects);
		if (closest_dist < close_enough || i > 100)
			return 1;
		if (closest_dist > 100)
			return 0;
		// ray "jumps" forward to a point where it might collide
		ray->distance += closest_dist;
		// updates location so that a new closest_dist can be calculated
		ray->location = v_sum(ray->location, v_mul(closest_dist, ray->direction));
		i++;
	}
	return 0;
}

/*	A new ray will check if there is an object between the collision point and the light source
	The ray gets a headstart towards the light byt the amount of self_collision_avoid */
int	light_obstructed(t_ray *ray, t_object *objects)
{
	t_ray	light_ray;
	t_object *light;
	double self_collision_avoid = 0.01;

	// copies location
	light_ray = *ray;
	light = get_object(objects, LIGHT);
	light_ray.direction = v_sub(light->location, light_ray.location);
	light_ray.direction = normalize_vector(light_ray.direction);
	light_ray.distance = self_collision_avoid;
	light_ray.location = v_sum(light_ray.location, v_mul(self_collision_avoid, light_ray.direction));
	return (cast_ray(&light_ray, objects, v_dist(light_ray.location, light->location) - self_collision_avoid));
}

void	raycast(t_data *data)
{
	int	x;
	int	y;
	t_ray ray;
	t_object *camera;

	camera = get_object(data->objects, CAMERA);
	if (camera == NULL)
	{
		printf("Camera not found\n");
		return ;
	}
	printf("Raycasting started\n");
	y = 0;
	while (y < Y)
	{
		x = 0;
		while (x < X)
		{
			ray = get_ray(camera, x, y);
			if (cast_ray(&ray, data->objects, RENDER_DISTANCE) == 1)
			{
				if (light_obstructed(&ray, data->objects) == 1)
					ray.color = BACKGROUND_COLOR; //SHADOW_COLOR;
			}
			else
				ray.color = BACKGROUND_COLOR;
			color_pixel(data->image, ray.color, x, y);
			x++;
		}
		printf("%d%%\r", ((y * 100) / Y));
		y++;
	}
	printf("Raycasting completed\n");
}
