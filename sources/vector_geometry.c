/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_geometry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:50:36 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 16:03:10 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * v_len - Computes the magnitude (length) of a 3D vector.
 *
 * @v: The vector whose length is to be calculated.
 *
 * Description:
 * The length (or magnitude) of a vector is given by:
 *     |v| = sqrt(v.x² + v.y² + v.z²)
 * This function is useful for normalizing vectors or computing distances.
 *
 * Return: The Euclidean norm (length) of the vector.
 */
double	v_len(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/**
 * v_dist - Computes the Euclidean distance between two 3D points.
 *
 * @a: The first point.
 * @b: The second point.
 *
 * Description:
 * The distance is calculated as:
 *     dist(a, b) = |a - b|
 * where subtraction between points results in a vector, and its magnitude
 * gives the distance. This is useful for determining object proximity
 * in ray tracing.
 *
 * Return: The Euclidean distance between points a and b.
 */
double	v_dist(t_vector a, t_vector b)
{
	return (v_len(v_sub(a, b)));
}


/**
 * normalize_vector - Normalizes a vector to unit length.
 *
 * @v: The vector to be normalized.
 *
 * Description:
 * The normalization is performed using the formula:
 *     v̂ = v / |v|
 * where |v| is the length of the vector. The resulting vector has a length
 * of exactly 1, which is crucial for direction calculations in ray tracing.
 * If the input vector is zero-length, behavior is undefined.
 *
 * Return: A unit vector in the same direction as v.
 */
t_vector	normalize_vector(t_vector v)
{
	double	len;

	len = v_len(v);
	return ((t_vector){v.x / len, v.y / len, v.z / len});
}
