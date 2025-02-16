#include "../includes/minirt.h"

int plane_collision(t_ray *ray, t_object *pl)
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

int	sphere_collision(t_ray *ray, t_object *sp)
{
	t_vector	oc;
	double		t;

	oc = v_sub(ray->start, sp->location);
	if (calc_t(&t, ray->direction, oc, sp->diameter / 2) == FAILURE || t >= ray->distance)
		return (NO_HIT);
	update_ray(ray, sp, t);
	return (HIT);
}

/* sign comes from which cap it is, -1 for "bottom" */
int cap_collision(t_ray *ray, t_object *cy, int sign) {
	t_vector cap_center, cap_normal, intersection_point;
	double t, denom;

	cap_normal = v_mul(sign, cy->orientation);
	cap_center = v_sum(cy->location, v_mul(cy->height / 2, cap_normal));
	denom = dot(ray->direction, cap_normal);
	if (fabs(denom) < EPSILON)
		return NO_HIT;
	t = dot(v_sub(cap_center, ray->start), cap_normal) / denom;
	if (t < 0 || t >= ray->distance)
		return NO_HIT;
	intersection_point = v_sum(ray->start, v_mul(t, ray->direction));
	if (dot(v_sub(intersection_point, cap_center), v_sub(intersection_point, cap_center)) <= (cy->diameter / 2) * (cy->diameter / 2))
	{
		if (t < ray->distance)
		{
			update_ray(ray, cy, t);
			ray->coll_norm = cap_normal; // override norm set in update_ray because this is the cap
			return HIT;
		}
	}
	return NO_HIT;
}

int	check_caps(t_ray *ray, t_object *cy)
{
	int	hit;

	if (cap_collision(ray, cy, 1) == HIT)
		hit = HIT;
	if (cap_collision(ray, cy, -1) == HIT)
		hit = HIT;
	return (hit);
}

int cylinder_collision(t_ray *ray, t_object *cy)
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