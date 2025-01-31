#include "../includes/minirt.h"

int	in_the_shadow(t_ray *ray, t_vector collision, t_object *light, t_object **arr)
{
	t_ray	shadow;
	shadow.start = ray->end;
	shadow.distance = DBL_MAX;
	shadow.direction = normalize_vector(v_sub(light->location, collision));
	if (cast_ray(&shadow, arr))
	{
		if (shadow.distance > v_dist(light->location, ray->start))
			return (0);
		else
			return (1);
	}
	return (0);
}

double	set_diffuse(t_vector normal, t_vector light_dir, double intensity)
{
	double	dot;
	dot = dot_product(normal, light_dir);
	if (dot < 0)
		return (0);
	return (intensity * dot);
}

uint32_t	set_lights(t_ray *ray, t_vector collision, t_vector normal, t_object **arr)
{
	t_object	*ambient;
	t_object	*light;
	t_vector	light_dir;
	double		diffuse;
	int			r;
	int			g;
	int			b;

	ambient = get_object(arr, AMBIENT);
	light = get_object(arr, LIGHT);
	diffuse = 0.0;
	light_dir = normalize_vector(v_sub(light->location, collision));
	if (!in_the_shadow(ray, collision, light, arr))
		diffuse = set_diffuse(normal, light_dir, light->brightness);
	r = min(255, (ambient->brightness + diffuse) * ((ray->color >> 16) & 0xff));
	g = min(255, (ambient->brightness + diffuse) * ((ray->color >> 8) & 0xff));
	b = min(255, (ambient->brightness + diffuse) * (ray->color & 0xff));
	return (255 << 24 | r << 16 | g << 8 | b);
}
