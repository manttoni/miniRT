/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandler2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:03 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 15:15:12 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * change_height - Adjusts the height of a cylinder object.
 *
 * @mlx_data: The key event data.
 * @selected: Pointer to the currently selected object.
 *
 * The function increases or decreases the height of a cylinder based
 * on the `PAGE_UP` and `PAGE_DOWN` keys. Ensures that the height
 * remains positive.
 *
 * Returns:
 * - SUCCESS if the height is modified.
 * - FAILURE if the selected object is not a cylinder or no change occurs.
 */
static int	change_height(mlx_key_data_t mlx_data, t_object *selected)
{
	double	delta;

	delta = 1;
	if (selected->type != CYLINDER)
		return (FAILURE);
	if (mlx_data.key == MLX_KEY_PAGE_DOWN
		&& selected->height - delta > 0)
		selected->height -= delta;
	else if (mlx_data.key == MLX_KEY_PAGE_UP
		&& selected->height + delta < DBL_MAX)
		selected->height += delta;
	else
		return (FAILURE);
	printf("Height: %f\n", selected->height);
	return (SUCCESS);
}

/**
 * change_diameter - Adjusts the diameter of a sphere or cylinder.
 *
 * @mlx_data: The key event data.
 * @selected: Pointer to the currently selected object.
 *
 * The function increases or decreases the diameter based on the
 * `KP_ADD` and `KP_SUBTRACT` keys. Ensures that the diameter remains
 * positive.
 *
 * Returns:
 * - SUCCESS if the diameter is modified.
 * - FAILURE if the selected object is not a sphere or cylinder or
 *   no change occurs.
 */
static int	change_diameter(mlx_key_data_t mlx_data, t_object *selected)
{
	double	delta;

	delta = 1;
	if (selected->type != CYLINDER && selected->type != SPHERE)
		return (FAILURE);
	if (mlx_data.key == MLX_KEY_KP_ADD
		&& selected->diameter + delta < DBL_MAX)
		selected->diameter += delta;
	else if (mlx_data.key == MLX_KEY_KP_SUBTRACT
		&& selected->diameter - delta > 0)
		selected->diameter -= delta;
	else
		return (FAILURE);
	printf("Diameter: %f\n", selected->diameter);
	printf("Height: %f\n", selected->height);
	return (SUCCESS);
}

/**
 * resize_object - Changes the size of a selected object.
 *
 * @mlx_data: The key event data.
 * @selected: Pointer to the currently selected object.
 *
 * Calls `change_height` for cylinders and `change_diameter` for
 * cylinders or spheres.
 *
 * Returns:
 * - SUCCESS if the object is resized.
 * - FAILURE if no size change occurs.
 */
int	resize_object(mlx_key_data_t mlx_data, t_object *selected)
{
	if (change_height(mlx_data, selected) == SUCCESS)
		return (SUCCESS);
	return (change_diameter(mlx_data, selected));
}

/**
 * adjust_brightness - Changes the brightness of a light source.
 *
 * @mlx_data: The key event data.
 * @selected: Pointer to the currently selected object.
 *
 * The function increases or decreases brightness using `KP_ADD` and
 * `KP_SUBTRACT` keys. Ensures brightness stays within the [0,1] range.
 *
 * Returns:
 * - SUCCESS if brightness is modified.
 * - FAILURE if no valid change occurs.
 */
int	adjust_brightness(mlx_key_data_t mlx_data, t_object *selected)
{
	double	delta;

	delta = 0.1;
	if (mlx_data.key == MLX_KEY_KP_ADD
		&& selected->brightness + delta <= 1)
		selected->brightness += delta;
	else if (mlx_data.key == MLX_KEY_KP_SUBTRACT
		&& selected->brightness - delta >= 0)
		selected->brightness -= delta;
	else
		return (FAILURE);
	printf("Brightness: %f\n", selected->brightness);
	return (SUCCESS);
}

/**
 * change_fov - Adjusts the field of view (FOV) of the camera.
 *
 * @mlx_data: The key event data.
 * @selected: Pointer to the currently selected camera object.
 *
 * The function increases or decreases the camera's FOV using the
 * `KP_ADD` and `KP_SUBTRACT` keys. Ensures the FOV remains between
 * 0 and 180 degrees.
 *
 * Returns:
 * - SUCCESS if the FOV is modified.
 * - FAILURE if no valid change occurs.
 */
int	change_fov(mlx_key_data_t mlx_data, t_object *selected)
{
	double	delta;

	delta = 10;
	if (mlx_data.key == MLX_KEY_KP_ADD && selected->fov + delta <= 180)
		selected->fov += delta;
	else if (mlx_data.key == MLX_KEY_KP_SUBTRACT && selected->fov - delta >= 0)
		selected->fov -= delta;
	else
		return (FAILURE);
	printf("Field of view: %d\n", selected->fov);
	return (SUCCESS);
}
