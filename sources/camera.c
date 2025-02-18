/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:53:05 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 11:53:08 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	camera_checks(int (**checks)(char *))
{
	checks[0] = &is_vector;
	checks[1] = &is_vector;
	checks[2] = &is_int;
	checks[3] = NULL;
}

int	assign_camera(t_object *camera, char **info)
{
	camera->location = parse_vector(info[1]);
	camera->orientation = parse_vector(info[2]);
	camera->fov = ft_atoi(info[3]);
	camera->orientation = normalize_vector(camera->orientation); // delete this line before eval
	if (camera->fov < 0 || camera->fov > 180)
		return (failure("FOV not valid"));
	camera->print_object = &print_camera;
	return (SUCCESS);
}

void	print_camera(t_object *c)
{
	printf("Camera:   📷\n");
	printf("Location: ");
	print_vector(c->orientation);
	printf("Orientation: ");
	print_vector(c->orientation);
}
