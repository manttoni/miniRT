/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:52:26 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 11:52:28 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_ray	get_reflection(t_ray *ray)
{
	t_ray	r;
	double	dot_p;

	dot_p = dot(ray->direction, ray->coll_norm);
	r.direction = v_sub(ray->direction, v_mul(2 * dot_p, ray->coll_norm));
	r.start = v_sum(ray->end, v_mul(EPSILON, r.direction));
	r.distance = DBL_MAX;
	r.color = BACKGROUND_COLOR;
	r.object = NULL;
	return (reflection);
}

uint32_t	mix_colors(uint32_t c1, uint32_t c2, double reflectivity)
{
	int	r;
	int	g;
	int	b;

	r = ((c1 >> 24) & 0xFF) * (1 - reflectivity)
		+ ((c2 >> 24) & 0xFF) * reflectivity;
	g = ((c1 >> 16) & 0xFF) * (1 - reflectivity)
		+ ((c2 >> 16) & 0xFF) * reflectivity;
	b = ((c1 >> 8) & 0xFF) * (1 - reflectivity)
		+ ((c2 >> 8) & 0xFF) * reflectivity;
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
	t_ray		r;

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
	if (reflections > 0 && is_collision && REFLECTIVITY > 0)
	{
		r = get_reflection(ray);
		if (cast_ray(&r, data, reflections - 1) == HIT)
			r.color = set_lights(data, &r, r.end, r.coll_norm);
		ray->color = mix_colors(ray->color, r.color, REFLECTIVITY);
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
			if (cast_ray(&ray, data, REFLECTIONS) == HIT)
				ray.color = set_lights(data, &ray, ray.end, ray.coll_norm);
			color_pixel(data->image, ray.color, x, y);
			x++;
		}
		printf("%d%%\r", y * 100 / Y);
		y++;
	}
	printf("Ready\r");
	fflush(stdout);
}
