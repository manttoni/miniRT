/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:19:02 by amaula            #+#    #+#             */
/*   Updated: 2025/02/20 13:05:18 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static t_ray	random_ray(t_ray *ray)
{
	t_ray		random;
	t_vector	dir;
	double		theta;
	double		phi;

	ft_memset(&random, 0, sizeof(t_ray));
	theta = (rand() / (double)RAND_MAX) * 2 * M_PI;  // Azimuthal angle [0, 2*pi]
	phi = (rand() / (double)RAND_MAX) * M_PI / 2;     // Polar angle [0, pi/2] (upper hemisphere)

	// Convert spherical to Cartesian coordinates
	dir.x = sin(phi) * cos(theta);
	dir.y = sin(phi) * sin(theta);
	dir.z = cos(phi);
	dir = normalize_vector(dir);
	// If the dot product is negative, reflect the vector to the correct hemisphere
	if (dot(ray->coll_norm, dir) < 0)
		dir = v_mul(-1, dir);
	random.start = ray->end;
	random.direction = dir;
	random.distance = DBL_MAX;
	random.color = BACKGROUND_COLOR;
	random.object = NULL;
	return (random);
}

static double	calc_brightness(uint32_t color)
{
	double	brightness;

	brightness = 0;
	brightness += ((color >> 24) & 0xFF) / (double)255;
	brightness += ((color >> 16) & 0xFF) / (double)255;
	brightness += ((color >> 8) & 0xFF) / (double)255;
	return (brightness / 3);
}

double	indirect_light(t_ray *ray, t_data *data)
{
	int		rays;
	int		i;
	t_ray	rand;
	double	brightness;

	if (REFLECTIONS == 0 || REFLECTIVITY == 0)
		return (0);
	i = 0;
	rays = INDIRECT_LIGHT_RAYS;
	brightness = 0;
	while (i < rays)
	{
		rand = random_ray(ray);
		if (cast_ray(&rand, data, 0) == HIT)
			brightness += calc_brightness(rand.color);
		i++;
	}
	return (REFLECTIVITY * brightness / rays);
}