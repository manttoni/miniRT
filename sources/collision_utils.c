/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:52:49 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 11:52:51 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector	compute_normal_curved(t_vector collision_point, t_object *cy)
{
	t_vector	to_point;
	t_vector	projection;
	t_vector	normal;

	to_point = v_sub(collision_point, cy->location);
	projection = v_mul(dot(to_point, cy->orientation), cy->orientation);
	normal = v_sub(to_point, projection);
	return (normalize_vector(normal));
}

void	update_ray(t_ray *ray, t_object *object, double t)
{
	ray->color = object->color;
	ray->distance = t;
	ray->end = v_sum(ray->start, v_mul(ray->distance, ray->direction));
	if (object->type == SPHERE)
		ray->coll_norm = normalize_vector(v_sub(ray->end, object->location));
	if (object->type == PLANE)
		ray->coll_norm = object->orientation;
	if (object->type == CYLINDER)
		ray->coll_norm = compute_normal_curved(ray->end, object);
	if (dot(ray->coll_norm, ray->direction) <= 0)
		ray->coll_norm = v_mul(-1, ray->coll_norm);
	ray->object = object;
}

/* Calculate collision point for curved surfaces
using t_disc struct to help with variables */
double	calc_t(double *t, t_vector v1, t_vector v2, double r)
{
	double	t1;
	double	t2;
	t_disc	disc;

	disc.a = dot(v1, v1);
	disc.b = 2 * dot(v1, v2);
	disc.c = dot(v2, v2) - r * r;
	disc.discriminant = disc.b * disc.b - 4 * disc.a * disc.c;
	if (disc.discriminant < 0)
		return (FAILURE);
	t1 = (-disc.b - sqrt(disc.discriminant)) / (2 * disc.a);
	t2 = (-disc.b + sqrt(disc.discriminant)) / (2 * disc.a);
	if (t1 < 0 && t2 < 0)
		return (FAILURE);
	if (t1 > 0)
		*t = t1;
	else
		*t = t2;
	return (SUCCESS);
}
