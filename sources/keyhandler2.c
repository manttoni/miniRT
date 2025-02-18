/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandler2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:42:12 by nzharkev          #+#    #+#             */
/*   Updated: 2025/02/18 13:42:14 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

int	resize_object(mlx_key_data_t mlx_data, t_object *selected)
{
	if (change_height(mlx_data, selected) == SUCCESS)
		return (SUCCESS);
	return (change_diameter(mlx_data, selected));
}

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
