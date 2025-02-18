/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:52:44 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 14:58:44 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * cap_collision - Checks if a ray intersects a cylinder's cap.
 *
 * @ray: Pointer to the ray being tested.
 * @cy: Pointer to the cylinder object.
 * @sign: Direction multiplier (1 for top cap, -1 for bottom cap).
 *
 * The function finds the intersection of the ray with a circular cap of
 * the cylinder:
 * - Checks if the ray is parallel to the cap (denominator close to zero).
 * - Computes the intersection point and verifies if it lies within the cap.
 * - Updates the ray if an intersection occurs.
 *
 * Returns:
 * - HIT if the ray intersects the cap.
 * - NO_HIT otherwise.
 */
static int	cap_collision(t_ray *ray, t_object *cy, int sign)
{
	t_cap_collision	c;

	c.cap_normal = v_mul(sign, cy->orientation);
	c.center = v_sum(cy->location, v_mul(cy->height / 2, c.cap_normal));
	c.denom = dot(ray->direction, c.cap_normal);
	if (fabs(c.denom) < EPSILON)
		return (NO_HIT);
	c.t = dot(v_sub(c.center, ray->start), c.cap_normal) / c.denom;
	if (c.t < 0 || c.t >= ray->distance)
		return (NO_HIT);
	c.collision = v_sum(ray->start, v_mul(c.t, ray->direction));
	if (dot(v_sub(c.collision, c.center), v_sub(c.collision, c.center))
		<= (cy->diameter / 2) * (cy->diameter / 2))
	{
		if (c.t < ray->distance)
		{
			update_ray(ray, cy, c.t);
			ray->coll_norm = c.cap_normal;
			if (dot(ray->coll_norm, ray->direction) <= 0)
				ray->coll_norm = v_mul(-1, ray->coll_norm);
			return (HIT);
		}
	}
	return (NO_HIT);
}

/**
 * check_caps - Checks for ray intersections with both cylinder caps.
 *
 * @ray: Pointer to the ray being tested.
 * @cy: Pointer to the cylinder object.
 *
 * Calls cap_collision() for both top and bottom caps.
 *
 * Returns:
 * - HIT if the ray hits either cap.
 * - NO_HIT otherwise.
 */
static int	check_caps(t_ray *ray, t_object *cy)
{
	int	hit;

	hit = NO_HIT;
	if (cap_collision(ray, cy, 1) == HIT)
		hit = HIT;
	if (cap_collision(ray, cy, -1) == HIT)
		hit = HIT;
	return (hit);
}

/**
 * cylinder_collision - Determines if a ray intersects a cylinder.
 *
 * @ray: Pointer to the ray being tested.
 * @cy: Pointer to the cylinder object.
 *
 * This function:
 * - Computes the intersection of the ray with the infinite cylinder by
 *   solving a quadratic equation.
 * - Checks if the intersection is within the height bounds.
 * - If the intersection is outside, checks the cylinder's caps.
 * - Updates the ray with the closest valid intersection.
 *
 * Returns:
 * - HIT if the ray intersects the cylinder.
 * - NO_HIT otherwise.
 */
int	cylinder_collision(t_ray *ray, t_object *cy)
{
	double			t;
	t_cylinder_coll	c;
	t_vector		mul1;
	t_vector		mul2;

	c.oc = v_sub(ray->start, cy->location);
	mul1 = v_mul(dot(ray->direction, cy->orientation), cy->orientation);
	c.proj_dir = v_sub(ray->direction, mul1);
	mul2 = v_mul(dot(c.oc, cy->orientation), cy->orientation);
	c.oc_proj = v_sub(c.oc, mul2);
	if (calc_t(&t, c.proj_dir, c.oc_proj, cy->diameter / 2) == FAILURE
		|| t > ray->distance)
		return (check_caps(ray, cy));
	c.coll_point = v_sum(ray->start, v_mul(t, ray->direction));
	c.height_proj = dot(v_sub(c.coll_point, cy->location), cy->orientation);
	if (fabs(c.height_proj) > cy->height / 2)
		return (check_caps(ray, cy));
	update_ray(ray, cy, t);
	check_caps(ray, cy);
	return (HIT);
}

/**
 * plane_collision - Determines if a ray intersects a plane.
 *
 * @ray: Pointer to the ray being tested.
 * @pl: Pointer to the plane object.
 *
 * This function computes the intersection of a ray with a plane using the
 * equation:
 *   t = (dot(N, P) - dot(N, O)) / dot(N, D)
 * where:
 * - N is the plane normal.
 * - P is a point on the plane.
 * - O is the ray origin.
 * - D is the ray direction.
 * - t is the intersection distance.
 *
 * If the denominator is too small (parallel ray) or t is out of range,
 * no hit occurs.
 *
 * Returns:
 * - HIT if the ray intersects the plane within a valid distance.
 * - NO_HIT otherwise.
 */
int	plane_collision(t_ray *ray, t_object *pl)
{
	double	denominator;
	double	numerator;
	double	t;
	double	d;

	d = dot(pl->orientation, pl->location);
	numerator = -dot(pl->orientation, ray->start) + d;
	denominator = dot(pl->orientation, ray->direction);
	if (fabs(denominator) < EPSILON)
		return (NO_HIT);
	t = numerator / denominator;
	if (t < EPSILON || t >= ray->distance)
		return (NO_HIT);
	update_ray(ray, pl, t);
	return (HIT);
}

/**
 * sphere_collision - Determines if a ray intersects a sphere.
 *
 * @ray: Pointer to the ray being tested.
 * @sp: Pointer to the sphere object.
 *
 * This function computes the intersection of a ray with a sphere by solving
 * the quadratic equation:
 *   dot(D, D) * t² + 2 * dot(D, (O - C)) * t + (dot(O - C, O - C) - r²) = 0
 * where:
 * - C is the sphere center.
 * - r is the sphere radius.
 * - O is the ray origin.
 * - D is the ray direction.
 * - t is the intersection distance.
 *
 * The closest valid positive t value is used.
 *
 * Returns:
 * - HIT if the ray intersects the sphere.
 * - NO_HIT otherwise.
 */
int	sphere_collision(t_ray *ray, t_object *sp)
{
	t_vector	oc;
	double		t;

	oc = v_sub(ray->start, sp->location);
	if (calc_t(&t, ray->direction, oc, sp->diameter / 2) == FAILURE
		|| t >= ray->distance)
		return (NO_HIT);
	update_ray(ray, sp, t);
	return (HIT);
}
