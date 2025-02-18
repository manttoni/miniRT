/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:28 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 11:54:29 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	rotate_object(t_object *object, t_vector new_orientation)
{
	object->orientation = normalize_vector(new_orientation);
	print_vector(object->orientation);
}

void	translate_object(t_object *object, t_vector delta)
{
	object->location = v_sum(object->location, delta);
	print_vector(object->location);
}

// Rodrigues' rotation formula
// Function to rotate a vector v around an arbitrary axis k by angle theta
void	rotate_vector(t_vector *v, t_vector k, float theta)
{
	float		cos_theta;
	float		sin_theta;
	float		dot_kv;
	t_vector	cross_kv;

	cos_theta = cos(theta);
	sin_theta = sin(theta);
	k = normalize_vector(k);
	dot_kv = dot(k, *v);
	cross_kv = cross_product(k, *v);
	v->x = v->x * cos_theta
		+ cross_kv.x * sin_theta
		+ k.x * dot_kv * (1 - cos_theta);
	v->y = v->y * cos_theta
		+ cross_kv.y * sin_theta
		+ k.y * dot_kv * (1 - cos_theta);
	v->z = v->z * cos_theta
		+ cross_kv.z * sin_theta
		+ k.z * dot_kv * (1 - cos_theta);
}
