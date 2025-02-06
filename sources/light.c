#include "../includes/minirt.h"

static int	in_the_shadow(t_ray *ray, t_vector collision, t_object *light, t_objarr *objarr)
{
	t_ray	shadow;

	(void)ray;
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

static double	set_specular(t_vector normal, t_vector light_dir, t_vector view_dir, double intensity, double shine)
{
	t_vector	halfway;
	double		dot;
	halfway = normalize_vector(v_sum(light_dir, view_dir));
	dot = dot_product(normal, halfway);
	if (dot < 0)
		return (0);
	return (intensity * pow(dot, shine));
}

static double	set_diffuse(t_vector normal, t_vector light_dir, double intensity)
{
	double	dot;
	// printf("Normal: x=%.2f, y=%.2f, z=%.2f\n", normal.x, normal.y, normal.z);
	// printf("Light Dir: x=%.2f, y=%.2f, z=%.2f\n", light_dir.x, light_dir.y, light_dir.z);
	dot = dot_product(normal, light_dir);
	// printf("Dot: %f\n", dot);
	if (dot < 0)
		return (0);
	return (intensity * dot);
}

uint32_t	set_lights(t_ray *ray, t_vector collision, t_vector normal, t_objarr *objarr)
{
	t_object	*ambient;
	t_object	*light;
	t_vector	light_dir;
	t_vector	view_dir;
	double		diffuse;
	double		specular;
	double		shine;
	uint32_t	color;
	int			r;
	int			g;
	int			b;

	ambient = get_object(objarr, AMBIENT);
	light = get_object(objarr, LIGHT);
	diffuse = 0.0;
	specular = 0.0;
	shine = 32.0;
	light_dir = normalize_vector(v_sub(light->location, collision));
	view_dir = normalize_vector(v_sub(ray->start, collision));
	if (!in_the_shadow(ray, collision, light, objarr))
	{
		diffuse = set_diffuse(normal, light_dir, light->brightness);
		specular = set_specular(normal, light_dir, view_dir, light->brightness, shine);
		// printf("Diffuse: %f\n", diffuse);
	}
	r = min(255, (ambient->brightness + diffuse + specular) * ((ray->color >> 24) & 0xff));
	g = min(255, (ambient->brightness + diffuse + specular) * ((ray->color >> 16) & 0xff));
	b = min(255, (ambient->brightness + diffuse + specular) * ((ray->color >> 8) & 0xff));
	color = (r << 24 | g << 16 | b << 8 | 255);
	return (color);
}
