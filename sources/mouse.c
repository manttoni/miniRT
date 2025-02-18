/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:39 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 16:15:34 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * left_click - Rotates the camera to face the selected point.
 *
 * @data: Pointer to the main scene data structure.
 *
 * This function retrieves the direction of the ray corresponding to the
 * current mouse position, then updates the camera's orientation accordingly.
 * The scene is redrawn after the camera rotation.
 */
static void	left_click(t_data *data)
{
	t_vector	new_ori;

	new_ori = get_ray(data->info, data->mouse.x, data->mouse.y).direction;
	rotate_object(data->camera, new_ori);
	redraw(data);
}

/**
 * right_click - Selects the object under the mouse cursor.
 *
 * @data: Pointer to the main scene data structure.
 *
 * This function casts a ray from the camera through the mouse position.
 * If the ray intersects an object, that object is selected.
 */
static void	right_click(t_data *data)
{
	t_ray	ray;

	ray = get_ray(data->info, data->mouse.x, data->mouse.y);
	if (cast_ray(&ray, data, 0) == 1)
	{
		if (data->selected != ray.object)
			select_object(ray.object, data);
	}
}

/**
 * rt_mouse - Handles mouse input for selecting and rotating objects.
 *
 * @param: Pointer to the main scene data structure.
 *
 * This function tracks mouse movement and button presses. If the left mouse
 * button is pressed, it rotates the camera toward the clicked direction.
 * If the right mouse button is pressed, it selects the object under the cursor.
 * The function also updates the mouse position relative to the window size.
 */
void	rt_mouse(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_get_mouse_pos(data->mlx, &(data->mouse.x), &(data->mouse.y));
	data->mouse.x *= (double)X / data->mlx->width;
	data->mouse.y *= (double)Y / data->mlx->height;
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT)
		&& !data->mouse.left)
	{
		data->mouse.left = 1;
		left_click(data);
	}
	else if (!mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
		data->mouse.left = 0;
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_RIGHT)
		&& !data->mouse.right)
	{
		data->mouse.right = 1;
		right_click(data);
	}
	else if (!mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_RIGHT))
		data->mouse.right = 0;
}
