#include "../includes/minirt.h"

double	in_the_shadow(t_vector collision, t_object *light, t_objarr *objarr)
{
	t_ray	shadow;
	double	light_dist;


	light_dist = 0.0;
	shadow.direction = normalize_vector(v_sub(light->location, collision));
	shadow.start = v_sum(collision, v_mul(EPSILON, shadow.direction));
	shadow.distance = DBL_MAX;
	if (cast_ray(&shadow, objarr))
	{
		light_dist = v_dist(light->location, collision);
		if (shadow.distance + EPSILON < v_dist(light->location, collision))
			return (fmax(0.2, shadow.distance / light_dist));
	}
	return (1.0);
}

double	set_specular(t_vector norm, t_light *light)
{
	t_vector	halfway;
	double		dot_p;

	halfway = normalize_vector(v_sum(light->light_dir, light->view_dir));
	dot_p = dot(norm, halfway);
	if (dot_p < 0)
		return (0);
	return (light->light->brightness * pow(fmax(dot_p, 0.0), light->shine));
}

double	set_diffuse(t_vector normal, t_light *light)
{
	double	dot_p;

	dot_p = dot(normal, light->light_dir);
	if (dot_p < 0)
		return (0);
	return (light->light->brightness * dot_p);
}
