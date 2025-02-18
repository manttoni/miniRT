/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:53:19 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 16:02:35 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * v_mul - Multiplies a vector by a scalar.
 *
 * @t: The scalar value.
 * @v: The vector to be scaled.
 *
 * Description:
 * Scalar multiplication of a vector scales each component by the scalar t:
 *     v' = (v.x * t, v.y * t, v.z * t)
 * This is useful for adjusting vector magnitudes, such as controlling light
 * intensity, ray direction scaling, and transformations in ray tracing.
 *
 * Return: A new vector where each component is scaled by t.
 */
t_vector	v_mul(double t, t_vector v)
{
	t_vector	product;

	product.x = v.x * t;
	product.y = v.y * t;
	product.z = v.z * t;
	return (product);
}

/**
 * v_sub - Subtracts two vectors.
 *
 * @v1: The first vector (minuend).
 * @v2: The second vector (subtrahend).
 *
 * Description:
 * Vector subtraction is performed component-wise:
 *     result = (v1.x - v2.x, v1.y - v2.y, v1.z - v2.z)
 * This operation is useful for computing direction vectors, such as
 * calculating the vector from a light source to a point in ray tracing.
 *
 * Return: A new vector that represents v1 - v2.
 */
t_vector	v_sub(t_vector v1, t_vector v2)
{
	t_vector	difference;

	difference.x = v1.x - v2.x;
	difference.y = v1.y - v2.y;
	difference.z = v1.z - v2.z;
	return (difference);
}

/**
 * v_sum - Adds two vectors.
 *
 * @v1: The first vector.
 * @v2: The second vector.
 *
 * Description:
 * Vector addition is performed component-wise:
 *     result = (v1.x + v2.x, v1.y + v2.y, v1.z + v2.z)
 * This is commonly used to compute positions, accumulate transformations,
 * and adjust light or camera positions in a 3D scene.
 *
 * Return: A new vector that represents v1 + v2.
 */
t_vector	v_sum(t_vector v1, t_vector v2)
{
	t_vector	sum;

	sum.x = v1.x + v2.x;
	sum.y = v1.y + v2.y;
	sum.z = v1.z + v2.z;
	return (sum);
}
