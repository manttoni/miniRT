/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:38:21 by nzharkev          #+#    #+#             */
/*   Updated: 2025/02/18 14:59:44 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
