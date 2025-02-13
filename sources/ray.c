#include "../includes/minirt.h"

/*	Returns a ray that is pointing towards pixel(x,y) of the image plane
	Camera holds precalculated data
		Basic vectors (u and v) of the image plane. Used for finding pixels
		All rays share some information like starting point and general direction
		aka camera direction	*/
t_ray	get_ray(t_image_plane info, int x, int y)
{
	t_ray		ray;

	ray = info.ray;
	ray.direction = v_sum(ray.direction, v_mul((-X / 2 + x + 0.5), info.u));
	ray.direction = v_sum(ray.direction, v_mul((-Y / 2 + y + 0.5), info.v));
	ray.direction = normalize_vector(ray.direction);
	return (ray);
}

/* Shoots a ray towards a pixel in the image plane
	if it hits something, returns 1, otherwise 0
	in case of 1, ray has been updated with values from the object it hit */
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
		if ((*(arr[i].collisionf))(ray, &arr[i]) == HIT)
			is_collision = 1;
		i++;
	}
	return (is_collision);
}

void	raycast(t_data *data)
{
	int	x;
	int	y;
	t_ray ray;

	y = 0;
	while (y < Y)
	{
		x = 0;
		while (x < X)
		{
			ray = get_ray(data->info, x, y);
			if (cast_ray(&ray, data->objects))
				ray.color = set_lights(data, &ray, ray.end, ray.coll_norm);
			// if (ray.color != BACKGROUND_COLOR)
			// {
			// 	printf("After color: \033[38;2;%d;%d;%dm%06X\033[0m\n",
			// 	(ray.color) & 0xFF, (ray.color >> 8) & 0xFF,
			// 	(ray.color >> 16) & 0xFF, ray.color);
			// }
			color_pixel(data->image, ray.color, x, y);
			x++;
		}
		y++;
	}
	printf("Ready\r");
	fflush(stdout);
}


