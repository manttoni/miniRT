/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:53:19 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 11:53:21 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector	v_mul(double t, t_vector v)
{
	t_vector	product;

	product.x = v.x * t;
	product.y = v.y * t;
	product.z = v.z * t;
	return (product);
}

t_vector	v_sub(t_vector v1, t_vector v2)
{
	t_vector	difference;

	difference.x = v1.x - v2.x;
	difference.y = v1.y - v2.y;
	difference.z = v1.z - v2.z;
	return (difference);
}

t_vector	v_sum(t_vector v1, t_vector v2)
{
	t_vector	sum;

	sum.x = v1.x + v2.x;
	sum.y = v1.y + v2.y;
	sum.z = v1.z + v2.z;
	return (sum);
}
