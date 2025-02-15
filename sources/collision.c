#include "../includes/minirt.h"

int plane_collision(t_ray *ray, t_object *pl)
{
	double	denominator;
	double	numerator;
	double	t;
	double	d;

	d = dot_product(pl->orientation, pl->location);
	numerator = -dot_product(pl->orientation, ray->start) + d;
	denominator = dot_product(pl->orientation, ray->direction);
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
	denom = dot_product(ray->direction, cap_normal);
	if (fabs(denom) < EPSILON)
		return NO_HIT;
	t = dot_product(v_sub(cap_center, ray->start), cap_normal) / denom;
	if (t < 0 || t >= ray->distance)
		return NO_HIT;
	intersection_point = v_sum(ray->start, v_mul(t, ray->direction));
	if (dot_product(v_sub(intersection_point, cap_center), v_sub(intersection_point, cap_center)) <= (cy->diameter / 2) * (cy->diameter / 2))
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
	double	t;
	t_vector	proj_dir;
	t_vector	oc_proj;
	t_vector	oc;
	t_vector	coll_point;
	double		height_proj;

    oc = v_sub(ray->start, cy->location);
	proj_dir = v_sub(ray->direction, v_mul(dot_product(ray->direction, cy->orientation), cy->orientation));
    oc_proj = v_sub(oc, v_mul(dot_product(oc, cy->orientation), cy->orientation));

	if (calc_t(&t, proj_dir, oc_proj, cy->diameter / 2) == FAILURE || t > ray->distance)
		return (check_caps(ray, cy));

    coll_point = v_sum(ray->start, v_mul(t, ray->direction));
    height_proj = dot_product(v_sub(coll_point, cy->location), cy->orientation);
    if (fabs(height_proj) > cy->height / 2)
        return (check_caps(ray, cy));
    update_ray(ray, cy, t);
	check_caps(ray, cy);
    return (HIT);
}

