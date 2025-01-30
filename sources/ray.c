#include "../includes/minirt.h"

/**
 * get_ray - Computes a ray for a given pixel on the image plane.
 * @camera: Pointer to the camera object.
 * @x: The horizontal pixel coordinate.
 * @y: The vertical pixel coordinate.
 *
 * This function:
 * - Uses the camera's **precomputed image plane vectors** (`u`, `v`).
 * - Adjusts the ray direction based on the **pixel position**.
 * - Normalizes the ray direction.
 *
 * Return:
 * - A `t_ray` struct representing the ray for pixel `(x, y)`.
 */
t_ray	get_ray(t_object *camera, int x, int y)
{
	t_ray		ray;

	ray = camera->info.ray;

	ray.direction = v_sum(ray.direction, v_mul((-X / 2 + x + 0.5), camera->info.u));
	ray.direction = v_sum(ray.direction, v_mul((-Y / 2 + y + 0.5), camera->info.v));
	ray.direction = normalize_vector(ray.direction);
	return (ray);
}

/**
 * cast_ray - Performs ray marching to find intersections.
 * @ray: Pointer to the ray being cast.
 * @objects: List of objects in the scene.
 * @render_distance: The maximum distance for rendering.
 *
 * This function:
 * - Iterates forward along the ray's direction.
 * - Checks the **closest object distance** at each step.
 * - Stops if an object is **close enough** (`close_enough` threshold).
 * - Limits iterations to prevent **infinite loops**.
 * - Returns `1` if the ray **hits an object**.
 * - Returns `0` if the ray **misses all objects**.
 *
 * Return:
 * - `1` if the ray **hits an object**.
 * - `0` if the ray **does not intersect anything**.
 */
int	cast_ray(t_ray *ray, t_object *objects, double render_distance)
{
	// double	closest_dist;
	// double	close_enough;
	// int		i;

	// i = 0;
	// close_enough = 0.001;
	// while (ray->distance < render_distance)
	// {
	// 	closest_dist = closest(ray, objects);
	// 	if (closest_dist < close_enough  || i < 100)
	// 		return (1);
	// 	if (closest_dist >= RENDER_DISTANCE)
	// 		return (0);
	// 	ray->location = v_sum(ray->location, v_mul(closest_dist, ray->direction));
	// 	i++;
	// }
	// return (0);
	double	closest_dist;
	double	close_enough;
	// double step;
	int		i;

	i = 0;
	close_enough = 0.0001;
	// step = 1.0;
	while (ray->distance < render_distance)
	{
		closest_dist = closest(ray, objects);
		if (closest_dist < close_enough)
			return (1);
		// step = fmax(0.1, closest_dist * 0.5);
		if (closest_dist < 0.1)
			closest_dist = 0.1;
		// ray->distance += step;
		ray->location = v_sum(ray->location, v_mul(closest_dist, ray->direction));
		if (i++ > 80)
			return (0);
	}
	return (0);
}

/**
 * light_obstructed - Determines if an object is blocking the light.
 * @ray: Pointer to the ray hitting an object.
 * @objects: List of objects in the scene.
 *
 * This function:
 * - Creates a **shadow ray** from the hit point **toward the light**.
 * - Checks if any object **blocks the path** to the light.
 * - Uses a small `self_collision_avoid` offset to prevent **self-shadowing**.
 * - Returns `1` if light is **obstructed** (in shadow).
 * - Returns `0` if light **reaches the point**.
 *
 * Return:
 * - `1` if **shadow is present**.
 * - `0` if **light reaches the point**.
 */
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

/**
 * raycast - Traces rays for each pixel and renders the scene.
 * @data: Pointer to the scene data structure.
 *
 * This function:
 * - Iterates over all pixels `(x, y)`.
 * - Computes the corresponding **camera ray**.
 * - Calls `cast_ray()` to check for intersections.
 * - Applies **lighting intensity based on distance**.
 * - Checks if the object is in **shadow**.
 * - Colors the pixel accordingly.
 */
void	raycast(t_data *data)
{
	int			x;
	int			y;
	t_ray		ray;
	t_object	*camera;
	// t_object	*light;
	// t_object	*hit;

	camera = get_object(data->objects, CAMERA);
	// light = get_object(data->objects, LIGHT);
	if (!camera)
	{
		printf("Camera or light not found\n");
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

			if (cast_ray(&ray, data->objects, RENDER_DISTANCE)
				&& ray.distance < RENDER_DISTANCE)
			{
				ray.color = color_intensity(ray.color, 1.0 - (ray.distance / RENDER_DISTANCE));
				if (light_obstructed(&ray, data->objects) == 1)
					ray.color = color_intensity(ray.color, 0.5);
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
