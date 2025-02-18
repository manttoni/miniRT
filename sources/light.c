/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:32:29 by nzharkev          #+#    #+#             */
/*   Updated: 2025/02/18 16:18:26 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * ambient_checks - Sets up validation checks for ambient light properties.
 *
 * @checks: Array of function pointers for validation.
 *
 * The function assigns:
 * - `is_double` to check ambient brightness.
 * - `is_color` to check ambient color.
 * - NULL to indicate the end of the checks.
 */
void	ambient_checks(int (**checks)(char *))
{
	checks[0] = &is_double;
	checks[1] = &is_color;
	checks[2] = NULL;
}

/**
 * lights_checks - Sets up validation checks for light source properties.
 *
 * @checks: Array of function pointers for validation.
 *
 * The function assigns:
 * - `is_vector` to check light position.
 * - `is_double` to check light brightness.
 * - NULL to indicate the end of the checks.
 */
void	lights_checks(int (**checks)(char *))
{
	checks[0] = &is_vector;
	checks[1] = &is_double;
	checks[2] = NULL;
}

/**
 * create_light - Initializes lighting calculations.
 *
 * @light: Pointer to the light object.
 * @ray: Pointer to the ray being processed.
 * @coll: The collision point where the light is interacting.
 *
 * Computes the light direction and view direction based on the collision point
 * and stores them in the `t_light` structure. Resets diffuse and specular
 * components to zero.
 */
static void	create_light(t_light *light, t_ray *ray, t_vector coll)
{
	light->diffuse = 0.0;
	light->specular = 0.0;
	light->shine = 2.0;
	light->light_dir = normalize_vector(v_sub(coll, light->obj->location));
	light->view_dir = normalize_vector(v_sub(ray->start, coll));
}

/**
 * set_lights - Computes the final color based on
 *              ambient, diffuse, and specular lighting.
 *
 * @data: Pointer to the scene data.
 * @ray: Pointer to the ray being processed.
 * @collision: The collision point where light calculations occur.
 *
 * The function initializes lighting, applies ambient lighting, calculates
 * shadows, and applies diffuse and specular lighting if the point is lit.
 * The final RGB values are clamped to the 0-255 range.
 *
 * Returns:
 * - The computed color as a 32-bit RGBA value.
 */
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
