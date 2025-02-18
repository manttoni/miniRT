/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:32:29 by nzharkev          #+#    #+#             */
/*   Updated: 2025/02/18 13:50:14 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	create_light(t_light *light, t_ray *ray, t_vector coll)
{
	light->diffuse = 0.0;
	light->specular = 0.0;
	light->shine = 2.0;
	light->light_dir = normalize_vector(v_sub(coll, light->obj->location));
	light->view_dir = normalize_vector(v_sub(ray->start, coll));
}

void	light_col(t_data *data, t_ray *ray, t_vector *f_col, double s_f)
{
	if (s_f > 0.2)
	{
		data->light->diffuse = set_diffuse(ray->coll_norm, data->light) * s_f;
		data->light->specular = set_specular(ray->coll_norm, data->light) * s_f;
		f_col->x += data->light->diffuse * ((ray->color >> 24) & 0xff) / 255.0;
		f_col->y += data->light->diffuse * ((ray->color >> 16) & 0xff) / 255.0;
		f_col->z += data->light->diffuse * ((ray->color >> 8) & 0xff) / 255.0;
		f_col->x += data->light->specular;
		f_col->y += data->light->specular;
		f_col->z += data->light->specular;
	}
}

uint32_t	set_lights(t_data *data, t_ray *ray, t_vector collision)
{
	t_vector	final_col;
	double		shadow_f;

	shadow_f = 1.0;
	create_light(data->light, ray, collision);
	data->ambient->color.x = ((data->ambient->obj->color >> 24) & 0xff) / 255.0;
	data->ambient->color.y = ((data->ambient->obj->color >> 16) & 0xff) / 255.0;
	data->ambient->color.z = ((data->ambient->obj->color >> 8) & 0xff) / 255.0;
	data->ambient->color = v_mul(data->ambient->obj->brightness,
			data->ambient->color);
	final_col = data->ambient->color;
	shadow_f = in_the_shadow(collision, data->light->obj, data);
	light_col(data, ray, &final_col, shadow_f);
	data->light->r = min(255, (int)(final_col.x * 255));
	data->light->g = min(255, (int)(final_col.y * 255));
	data->light->b = min(255, (int)(final_col.z * 255));
	data->light->color = (data->light->r << 24 | data->light->g << 16
			| data->light->b << 8 | 255);
	return (data->light->color);
}
