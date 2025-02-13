#include "../includes/minirt.h"

static int	in_the_shadow(t_vector collision, t_object *light, t_objarr *objarr)
{
	t_ray	shadow;

	shadow.direction = normalize_vector(v_sub(light->location, collision));
	shadow.start = v_sum(collision, v_mul(EPSILON, shadow.direction));
	shadow.distance = DBL_MAX;
	if (cast_ray(&shadow, objarr))
		if (shadow.distance + EPSILON < v_dist(light->location, collision))
			return (1);
	return (0);
}

static double	set_specular(t_vector norm, t_light *light)
{
	t_vector	halfway;
	double		dot;

	halfway = normalize_vector(v_sum(light->light_dir, light->view_dir));
	dot = dot_product(norm, halfway);
	if (dot < 0)
		return (0);
	return (light->light->brightness * pow(dot, light->shine));
}

static double	set_diffuse(t_vector normal, t_light *light)
{
	double	dot;

	dot = dot_product(normal, light->light_dir);
	if (dot < 0)
		return (0);
	return (light->light->brightness * dot);
}

void	ambient_checks(int (**checks)(char *))
{
		checks[0] = &is_double;
		checks[1] = &is_color;
		checks[2] = NULL;
}

void	lights_checks(int (**checks)(char *))
{
		checks[0] = &is_vector;
		checks[1] = &is_double;
		checks[2] = NULL;
}

void	create_light(t_light *light, t_ray *ray, t_vector collision)
{
	light->diffuse = 0.0;
	light->specular = 0.0;
	light->shine = 32.0;
	light->light_dir = normalize_vector(v_sub(collision, light->light->location));
	light->view_dir = normalize_vector(v_sub(ray->start, collision));
}

uint32_t	set_lights(t_data *data, t_ray *ray, t_vector collision, t_vector normal)
{
	create_light(data->light, ray, collision);
	if (dot_product(normal, data->light->light_dir) < 0)
		normal = v_mul(-1, normal);
	if (!in_the_shadow(collision, data->light->light, data->objects))
	{
		data->light->diffuse = set_diffuse(normal, data->light);
		data->light->specular = set_specular(normal, data->light);
	}
	data->light->r = min(255, (data->light->ambient->brightness + data->light->diffuse + data->light->specular) * ((ray->color >> 24) & 0xff));
	data->light->g = min(255, (data->light->ambient->brightness + data->light->diffuse + data->light->specular) * ((ray->color >> 16) & 0xff));
	data->light->b = min(255, (data->light->ambient->brightness + data->light->diffuse + data->light->specular) * ((ray->color >> 8) & 0xff));
	data->light->color = (data->light->r << 24 | data->light->g << 16 | data->light->b << 8 | 255);
	return (data->light->color);
}
