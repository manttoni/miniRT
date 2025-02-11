#include "../includes/minirt.h"

static int	in_the_shadow(t_vector collision, t_object *light, t_objarr *objarr)
{
	t_ray	shadow;

	shadow.direction = normalize_vector(v_sub(light->location, collision));
	shadow.start = v_sum(collision, v_mul(0.001, shadow.direction));
	shadow.distance = DBL_MAX;
	if (cast_ray(&shadow, objarr))
	{
		if (shadow.distance < v_dist(light->location, collision))
			return (1);
	}
	return (0);
}

static double	set_specular(t_vector norm, t_vector l_dir, t_vector v_dir, double intensity, double shine)
{
	t_vector	halfway;
	double		dot;

	halfway = normalize_vector(v_sum(l_dir, v_dir));
	dot = dot_product(norm, halfway);
	if (dot < 0)
		return (0);
	return (intensity * pow(dot, shine));
}

static double	set_diffuse(t_vector normal, t_vector light_dir, double intensity)
{
	double	dot;

	dot = dot_product(normal, light_dir);
	if (dot < 0)
		return (0);
	return (intensity * dot);
}

void	create_light(t_light *light, t_ray *ray, t_vector collision)
{
	light->diffuse = 0.0;
	light->specular = 0.0;
	light->shine = 32.0;
	light->light_dir = normalize_vector(v_sub(light->light->location, collision));
	light->view_dir = normalize_vector(v_sub(ray->start, collision));
}

uint32_t	set_lights(t_data *data, t_ray *ray, t_vector collision, t_vector normal)
{
	create_light(data->light, ray, collision);
	if (!in_the_shadow(collision, data->light->light, data->objects))
	{
		if (dot_product(normal, data->light->view_dir) < 0)
			normal = v_mul(-1, normal);
		data->light->diffuse = set_diffuse(normal, data->light->light_dir, data->light->light->brightness);
		data->light->specular = set_specular(normal, data->light->light_dir, data->light->view_dir, data->light->light->brightness, data->light->shine);
	}
	data->light->r = min(255, (data->light->ambient->brightness + data->light->diffuse + data->light->specular) * ((ray->color >> 24) & 0xff));
	data->light->g = min(255, (data->light->ambient->brightness + data->light->diffuse + data->light->specular) * ((ray->color >> 16) & 0xff));
	data->light->b = min(255, (data->light->ambient->brightness + data->light->diffuse + data->light->specular) * ((ray->color >> 8) & 0xff));
	data->light->color = (data->light->r << 24 | data->light->g << 16 | data->light->b << 8 | 255);
	return (data->light->color);
}
