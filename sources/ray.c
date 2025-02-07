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

int	cast_ray(t_ray *ray, t_objarr *objarr)
{
	size_t	i;
	int		is_collision;
	t_object	*arr;

	is_collision = 0;
	i = 0;
	arr = objarr->arr;
	while (i < objarr->objects)
	{
		if (arr[i].collisionf != NULL)
			is_collision = max(is_collision, (*(arr[i].collisionf))(ray, arr[i]));
		i++;
	}
	return (is_collision);
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
			// if (ray.color != BACKGROUND_COLOR)
			// {
			// 	printf("Before color: \033[38;2;%d;%d;%dm%06X\033[0m\n",
			// 	(ray.color) & 0xFF, (ray.color >> 8) & 0xFF,
			// 	(ray.color >> 16) & 0xFF, ray.color);
			// }
			if (cast_ray(&ray, data->objects))
				ray.color = set_lights(&ray, ray.end, ray.coll_norm, data->objects);
			// if (ray.color == BACKGROUND_COLOR)
			// {
			// 	printf("After color: \033[38;2;%d;%d;%dm%06X\033[0m\n",
			// 	(ray.color >> 24) & 0xFF, (ray.color >> 16) & 0xFF,
			// 	(ray.color >> 8) & 0xFF, ray.color);
			// }
			color_pixel(data->image, ray.color, x, y);
			x++;
		}
		y++;
	}
}


