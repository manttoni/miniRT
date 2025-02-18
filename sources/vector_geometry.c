/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_geometry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:50:36 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 11:50:51 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	v_len(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	v_dist(t_vector a, t_vector b)
{
	return (v_len(v_sub(a, b)));
}

t_vector	normalize_vector(t_vector v)
{
	double	len;

	len = v_len(v);
	return ((t_vector){v.x / len, v.y / len, v.z / len});
}
