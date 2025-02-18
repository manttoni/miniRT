/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:28 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 15:49:25 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * rotate_object - Rotates an object by setting a new orientation.
 *
 * @object: The object whose orientation is being updated.
 * @new_orientation: The new orientation vector for the object.
 *
 * This function normalizes the provided new_orientation vector
 * and assigns it to the object's orientation. It then prints
 * the updated orientation.
 */
void	rotate_object(t_object *object, t_vector new_orientation)
{
	object->orientation = normalize_vector(new_orientation);
	print_vector(object->orientation);
}

/**
 * translate_object - Moves an object by a given translation vector.
 *
 * @object: The object to be moved.
 * @delta: The translation vector specifying the movement.
 *
 * This function updates the object's location by adding the delta
 * vector to its current position. The new location is then printed.
 */
void	translate_object(t_object *object, t_vector delta)
{
	object->location = v_sum(object->location, delta);
	print_vector(object->location);
}


/**
 * rotate_vector - Rotates a vector around a given axis.
 *
 * @v: Pointer to the vector to be rotated.
 * @k: The axis of rotation (must be a unit vector).
 * @theta: The angle of rotation in radians.
 *
 * This function rotates the vector @v around the axis @k by
 * an angle @theta using Rodrigues' rotation formula:
 *
 * v' = v * cos(theta) + (k x v) * sin(theta) + k * (k ⋅ v) * (1 - cos(theta))
 *
 * If @k is not normalized, it will be normalized before use.
 */
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
