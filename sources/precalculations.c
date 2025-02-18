/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precalculations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:30:15 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 12:30:20 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/* Calculates the distance to the image plane 
from the camera so that the angle is fov */
double	calc_view_distance(int fov)
{
	double	fov_rad;

	fov_rad = fov * M_PI / 180;
	return ((X / 2) / tan(fov_rad / 2));
}

t_image_plane	image_plane(t_object *camera)
{
	t_image_plane	info;
	t_vector		up;

	info.view_distance = calc_view_distance(camera->fov);
	up = vector(0, 1, 0);
	if (fabs(camera->orientation.y) > 0.99)
		up = vector(1, 0, 0);
	info.u = normalize_vector(cross_product(up, camera->orientation));
	info.v = normalize_vector(cross_product(camera->orientation, info.u));
	if (dot(info.v, up) < 0)
		info.v = v_mul(-1, info.v);
	info.ray.start = camera->location;
	info.ray.end = camera->location;
	info.ray.direction = v_mul(info.view_distance, camera->orientation);
	info.ray.direction = v_sum(camera->location, info.ray.direction);
	info.ray.color = BACKGROUND_COLOR;
	info.ray.distance = DBL_MAX;
	info.ray.object = NULL;
	return (info);
}

void	set_precalculations(t_data *data)
{
	data->info = image_plane(data->camera);
}
