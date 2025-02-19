/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:38:21 by nzharkev          #+#    #+#             */
/*   Updated: 2025/02/19 11:49:21 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * mix_colors - Blends two colors based on reflectivity.
 *
 * @c1: The base color (original object color).
 * @c2: The reflection color.
 * @reflectivity: The blending factor (0 = no reflection, 1 = full reflection).
 *
 * This function linearly interpolates between two colors using
 * the reflectivity factor. The higher the reflectivity, the more
 * the reflection color dominates.
 *
 * Returns: The blended color as a 32-bit ARGB value.
 */
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

/**
 * light_col - Computes the diffuse and specular lighting contributions.
 *
 * @data: Pointer to the scene data.
 * @ray: Pointer to the ray being processed.
 * @f_col: Pointer to the final color vector to be updated.
 * @s_f: Shadow factor determining light intensity contribution.
 *
 * If `s_f` (shadow factor) is greater than 0.2, the function calculates the
 * diffuse and specular lighting contributions and adds them to the final color.
 */
void	light_col(t_data *data, t_ray *ray, t_vector *f_col, double s_f)
{
	if (s_f > 0.2)
	{
		if (dot(ray->coll_norm, data->light->light_dir) < 0)
			ray->coll_norm = v_mul(-1, ray->coll_norm);
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

/**
 * color_pixel - Colors a pixel in the image at the given coordinates.
 *
 * @image: Pointer to the MLX image where the pixel will be colored.
 * @pixel_color: 32-bit color value (RGBA format).
 * @x: X-coordinate of the pixel.
 * @y: Y-coordinate of the pixel.
 *
 * This function ensures that the pixel coordinates are within the valid range
 * before calling `mlx_put_pixel()`. This prevents out-of-bounds errors when
 * rendering the image.
 */
void	color_pixel(mlx_image_t *image, uint32_t pixel_color, int x, int y)
{
	if (x >= 0 && x < X && y >= 0 && y < Y)
		mlx_put_pixel(image, x, y, pixel_color);
}
