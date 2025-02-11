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

static void	create_light(t_light *light, t_ray *ray, t_vector collision, t_objarr *objarr)
{
	light->ambient = get_object(objarr, AMBIENT);
	light->light = get_object(objarr, LIGHT);
	light->diffuse = 0.0;
	light->specular = 0.0;
	light->shine = 32.0;
	light->light_dir = normalize_vector(v_sub(light->light->location, collision));
	light->view_dir = normalize_vector(v_sub(ray->start, collision));
}

uint32_t	set_lights(t_ray *ray, t_vector collision, t_vector normal, t_objarr *objarr)
{
	t_light	light;

	create_light(&light, ray, collision, objarr);
	if (dot_product(normal, light.view_dir) < 0)
		normal = v_mul(-1, normal);
	if (!in_the_shadow(collision, light.light, objarr))
	{
		light.diffuse = set_diffuse(normal, light.light_dir, light.light->brightness);
		light.specular = set_specular(normal, light.light_dir, light.view_dir, light.light->brightness, light.shine);
	}
	light.r = min(255, (light.ambient->brightness + light.diffuse + light.specular) * ((ray->color >> 24) & 0xff));
	light.g = min(255, (light.ambient->brightness + light.diffuse + light.specular) * ((ray->color >> 16) & 0xff));
	light.b = min(255, (light.ambient->brightness + light.diffuse + light.specular) * ((ray->color >> 8) & 0xff));
	light.color = (light.r << 24 | light.g << 16 | light.b << 8 | 255);
	return (light.color);
}
