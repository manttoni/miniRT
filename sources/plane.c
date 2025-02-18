/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:51:09 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 11:51:11 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	plane_checks(int (**checks)(char *))
{
	checks[0] = &is_vector;
	checks[1] = &is_vector;
	checks[2] = &is_color;
	checks[3] = NULL;
}

int	assign_plane(t_object *plane, char **info)
{
	plane->location = parse_vector(info[1]);
	plane->orientation = parse_vector(info[2]);
	if ((plane->orientation.x > 1.0 || plane->orientation.x < -1.0)
		|| (plane->orientation.y > 1.0 || plane->orientation.y < -1.0)
		|| (plane->orientation.z > 1.0 || plane->orientation.z < -1.0))
		return (failure("Orientation should be [1.0, -1.0]"));
	plane->color = parse_color(info[3]);
	plane->orientation = normalize_vector(plane->orientation); // delete this line before eval
	if (!is_normalized_vector(plane->orientation))
		return (failure("Plane orientation not normalized"));
	plane->collisionf = &plane_collision;
	plane->print_object = &print_plane;
	return (SUCCESS);
}

void	print_plane(t_object *p)
{
	printf("Plane:    ✈️\n");
	printf("Location: ");
	print_vector(p->location);
	printf("Orientation: ");
	print_vector(p->orientation);
	printf("Color: ");
	print_color(p->color);
}
