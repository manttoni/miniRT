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

t_ray reflect(t_ray *ray)
{
	t_ray	reflection;
    double dot_product;
	
	dot_product = dot(ray->direction, ray->coll_norm);
    reflection.direction = v_sub(ray->direction, v_mul(2 * dot_product, ray->coll_norm));
	reflection.start = v_sum(ray->end, v_mul(EPSILON, reflection.direction));
	reflection.distance = DBL_MAX;
	reflection.color = BACKGROUND_COLOR;
	reflection.object = NULL;
    return reflection;
}

uint32_t	mix_colors(uint32_t c1, uint32_t c2, double refl_str)
{
	int	r;
	int	g;
	int	b;

	r = (((c1 >> 24) & 0xFF) + refl_str * ((c2 >> 24) & 0xFF)) / (1 + refl_str);
	g = (((c1 >> 16) & 0xFF) + refl_str * ((c2 >> 16) & 0xFF)) / (1 + refl_str);
	b = (((c1 >> 8) & 0xFF) + refl_str * ((c2 >> 8) & 0xFF)) / (1 + refl_str);

	return (r << 24 | g << 16 | b << 8 | 255);
}

/* Shoots a ray towards a pixel in the image plane
	if it hits something, returns 1, otherwise 0
	in case of 1, ray has been updated with values from the object it hit */
int	cast_ray(t_ray *ray, t_data *data, int reflections)
{
	size_t		i;
	int			is_collision;
	t_object	*arr;
	t_ray		reflection;

	is_collision = 0;
	i = 0;
	arr = data->objects->arr;
	while (i < data->objects->objects)
	{
		if ((*(arr[i].collisionf))(ray, &arr[i]) == HIT)
		{
			is_collision = 1;
		}
		i++;
	}
	if (reflections > 0 && is_collision)
	{
		reflection = reflect(ray);
		cast_ray(&reflection, data, reflections - 1);
		reflection.color = set_lights(data, &reflection, reflection.end, reflection.coll_norm);
		ray->color = mix_colors(ray->color, reflection.color, 1000);
	}
	return (is_collision);
}

void	raycast(t_data *data)
{
	int		x;
	int		y;
	t_ray	ray;

	y = 0;
	while (y < Y)
	{
		x = 0;
		while (x < X)
		{
			ray = get_ray(data->info, x, y);
			if (cast_ray(&ray, data, 10) == HIT)
				ray.color = set_lights(data, &ray, ray.end, ray.coll_norm);
			// if (ray.color == BACKGROUND_COLOR)
			// {
			// 	printf("After color: \033[38;2;%d;%d;%dm%06X\033[0m\n",
			// 	(ray.color >> 24) & 0xFF, (ray.color >> 8) & 0xFF,
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
