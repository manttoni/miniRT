#include "../includes/minirt.h"

/*	Returns a ray that is pointing towards pixel(x,y) of the image plane
	Camera holds precalculated data
		Basic vectors (u and v) of the image plane. Used for finding pixels
		All rays share some information like starting point and general direction
		aka camera direction	*/
static t_ray	get_ray(t_object *camera, int x, int y)
{
	t_ray		ray;

	ray = camera->info.ray;
	ray.direction = v_sum(ray.direction, v_mul((-X / 2 + x + 0.5), camera->info.u));
	ray.direction = v_sum(ray.direction, v_mul((-Y / 2 + y + 0.5), camera->info.v));
	ray.direction = normalize_vector(ray.direction);
	return (ray);
}

int	cast_ray(t_ray *ray, t_object **arr)
{
	size_t	i;
	int		is_collision;

	is_collision = 0;
	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i]->collisionf != NULL)
			is_collision = max(is_collision, (*arr[i]->collisionf)(ray, arr[i]));
		i++;
	}
	return is_collision;
}

void	raycast(t_data *data)
{
	int	x;
	int	y;
	t_ray ray;
	t_object *camera;

	camera = get_object(data->objects->arr, CAMERA);
	camera = get_object(data->objects->arr, CAMERA);
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
			cast_ray(&ray, data->objects->arr);
			// if (ray.color != BACKGROUND_COLOR)
			// {
			// 	printf("Before color: \033[38;2;%d;%d;%dm%06X\033[0m\n",
			// 	(ray.color) & 0xFF, (ray.color >> 8) & 0xFF,
			// 	(ray.color >> 16) & 0xFF, ray.color);
			// }
			ray.color = set_lights(&ray, ray.end, ray.coll_norm, data->objects->arr);
			// if (ray.color != BACKGROUND_COLOR)
			// {
			// 	printf("After color: \033[38;2;%d;%d;%dm%06X\033[0m\n",
			// 	(ray.color) & 0xFF, (ray.color >> 8) & 0xFF,
			// 	(ray.color >> 16) & 0xFF, ray.color);
			// }
			color_pixel(data->image, ray.color, x, y);
			x++;
		}
		printf("%d%%\r", ((y * 100) / Y));
		y++;
	}
	printf("Raycasting completed\n");
}


