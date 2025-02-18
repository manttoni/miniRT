/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:39 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 11:54:40 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/* Rotates camera to look at the cursor*/
void	left_click(t_data *data)
{
	t_vector	new_ori;

	new_ori = get_ray(data->info, data->mouse.x, data->mouse.y).direction;
	rotate_object(data->camera, new_ori);
	redraw(data);
}

/* Selects an object at the cursor*/
void	right_click(t_data *data)
{
	t_ray	ray;

	ray = get_ray(data->info, data->mouse.x, data->mouse.y);
	if (cast_ray(&ray, data, 0) == 1)
	{
		if (data->selected != ray.object)
			select_object(ray.object, data);
	}
}

/* mouse.left and mouse.right checks prevent 
the program from executing the functions every frame */
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
