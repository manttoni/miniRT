#include "../includes/minirt.h"

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
	light->shine = 2.0;
	light->light_dir = normalize_vector(v_sub(collision, light->light->location));
	light->view_dir = normalize_vector(v_sub(ray->start, collision));
}

void	coloring_light(t_data *data, t_ray *ray, t_vector *final_col, t_vector normal, double shadow_f)
{
	if (shadow_f > 0.2)
	{
	data->light->diffuse = set_diffuse(normal, data->light) * shadow_f;
	data->light->specular = set_specular(normal, data->light) * shadow_f;
	final_col->x += data->light->diffuse * ((ray->color >> 24) & 0xff) / 255.0;
	final_col->y += data->light->diffuse * ((ray->color >> 16) & 0xff) / 255.0;
	final_col->z += data->light->diffuse * ((ray->color >> 8) & 0xff) / 255.0;
	final_col->x += data->light->specular;
	final_col->y += data->light->specular;
	final_col->z += data->light->specular;
	}
}

uint32_t	set_lights(t_data *data, t_ray *ray, t_vector collision, t_vector normal)
{
	t_vector	final_col;
	double		shadow_f;

	shadow_f = 1.0;
	create_light(data->light, ray, collision);
	if (dot(normal, data->light->light_dir) < 0)
		normal = v_mul(-1, normal);
	data->ambient->ambient_col.x = ((data->ambient->ambient->color >> 24) & 0xff) / 255.0;
	data->ambient->ambient_col.y = ((data->ambient->ambient->color >> 16) & 0xff) / 255.0;
	data->ambient->ambient_col.z = ((data->ambient->ambient->color >> 8) & 0xff) / 255.0;
	data->ambient->ambient_col = v_mul(data->ambient->ambient->brightness, data->ambient->ambient_col);
	final_col = data->ambient->ambient_col;
	shadow_f = in_the_shadow(collision, data->light->light, data->objects);
	coloring_light(data, ray, &final_col, normal, shadow_f);
	// final_col.x += final_col.x * shadow_f + data->ambient->ambient_col.x * (1 - shadow_f);
	// final_col.y += final_col.y * shadow_f + data->ambient->ambient_col.y * (1 - shadow_f);
	// final_col.z += final_col.z * shadow_f + data->ambient->ambient_col.z * (1 - shadow_f);
	data->light->r = min(255, (int)(final_col.x * 255));
	data->light->g = min(255, (int)(final_col.y * 255));
	data->light->b = min(255, (int)(final_col.z * 255));
	data->light->color = (data->light->r << 24 | data->light->g << 16 | data->light->b << 8 | 255);
	return (data->light->color);
}
