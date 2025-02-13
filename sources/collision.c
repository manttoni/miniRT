#include "../includes/minirt.h"

static void	update_ray(t_ray *ray, t_object *object, double t)
{
	ray->color = object->color;
	ray->distance = t;
	ray->end = v_sum(ray->start, v_mul(ray->distance, ray->direction));
	if (object->type == SPHERE)
		ray->coll_norm = normalize_vector(v_sub(ray->end, object->location));
	if (object->type == PLANE)
		ray->coll_norm = object->orientation;
	ray->object = object;
}

/*	numerator is a precalculated value stored in t_object */
int plane_collision(t_ray *ray, t_object *pl)
{
	double denominator;
	double t;
	double	d;

	d = dot_product(pl->orientation, pl->location);
	//ray->start = v_sum(ray->start, vector(0.0001, 0.0001, 0.0001));
	pl->numerator = -dot_product(pl->orientation, ray->start) + d;
	denominator = dot_product(pl->orientation, ray->direction);
	if (fabs(denominator) < EPSILON)
		return (NO_HIT);
	t = pl->numerator / denominator;
	if (t < 0.1 || t >= ray->distance)
		return (NO_HIT);
	update_ray(ray, pl, t);
	return (HIT);
}

/* if ray collides with sp, ray updates its variables
	and func returns 1, otherwise 0*/
int	sphere_collision(t_ray *ray, t_object *sp)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
	t_vector oc;

	oc = v_sub(ray->start, sp->location);
	a = dot_product(ray->direction, ray->direction);
	b = 2 * dot_product(ray->direction, oc);
	c = dot_product(oc, oc) - (sp->diameter / 2) * (sp->diameter / 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (NO_HIT);
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t1 < 0 && t2 < 0)
		return (NO_HIT);
	double t = (t1 > 0) ? t1 : t2;
	if (t >= ray->distance)
		return (NO_HIT);
	update_ray(ray, sp, t);
	return (HIT);
}

t_vector compute_normal_curved(t_vector collision_point, t_object *cy) {
    t_vector to_point = v_sub(collision_point, cy->location);
    t_vector projection = v_mul(dot_product(to_point, cy->orientation), cy->orientation);
    t_vector normal = v_sub(to_point, projection);
    return normalize_vector(normal);
}
t_vector compute_normal_cap(int cap_side, t_object *cy) {
    return (cap_side == TOP_CYLINDER_CAP) ? cy->orientation : v_mul(-1, cy->orientation);
}

int cap_collision(t_ray *ray, t_object *cy, int cap_side) {
	t_vector cap_center, cap_normal, intersection_point;
	double t;

	cap_normal = cy->orientation; // top cap: same as cylinder orientation
	if (cap_side == BOTTOM_CYLINDER_CAP)
	{
		cap_normal = v_mul(-1, cy->orientation); // bottom cap: opposite of cylinder orientation
	}

	cap_center = v_sum(cy->location, v_mul(cap_side == TOP_CYLINDER_CAP ? cy->height / 2 : -cy->height / 2, cy->orientation));
	double denom = dot_product(ray->direction, cap_normal);
	if (fabs(denom) < EPSILON)
	{
		return NO_HIT; // The ray is parallel to the cap, no intersection
	}

	t = dot_product(v_sub(cap_center, ray->start), cap_normal) / denom;

	if (t < 0 || t >= ray->distance)
		return NO_HIT;

	intersection_point = v_sum(ray->start, v_mul(t, ray->direction));
	if (dot_product(v_sub(intersection_point, cap_center), v_sub(intersection_point, cap_center)) <= (cy->diameter / 2) * (cy->diameter / 2))
	{
		ray->coll_norm = compute_normal_cap(cap_side, cy);
		update_ray(ray, cy, t);
		return HIT;
	}

	return NO_HIT;
}

int	check_caps(t_ray *ray, t_object *cy)
{
	int	hit;

	hit = max(cap_collision(ray, cy, TOP_CYLINDER_CAP) == HIT, cap_collision(ray, cy, BOTTOM_CYLINDER_CAP));
	return (hit);
}

int cylinder_collision(t_ray *ray, t_object *cy)
{
    t_vector oc, proj_dir, oc_proj, coll_point;
    double a, b, c, discriminant, t1, t2, t;
    double height_proj;

    oc = v_sub(ray->start, cy->location);
    proj_dir = v_sub(ray->direction, v_mul(dot_product(ray->direction, cy->orientation), cy->orientation));
    oc_proj = v_sub(oc, v_mul(dot_product(oc, cy->orientation), cy->orientation));

    a = dot_product(proj_dir, proj_dir);
    b = 2 * dot_product(proj_dir, oc_proj);
    c = dot_product(oc_proj, oc_proj) - (cy->diameter / 2) * (cy->diameter / 2);
    discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return (check_caps(ray, cy));

    t1 = (-b - sqrt(discriminant)) / (2 * a);
    t2 = (-b + sqrt(discriminant)) / (2 * a);

    if (t1 >= 0 && t1 < ray->distance)
        t = t1;
    else if (t2 >= 0 && t2 < ray->distance)
        t = t2;
    else
        return (check_caps(ray, cy)); // if doesnt hit curved part, check if it hits a cap

    coll_point = v_sum(ray->start, v_mul(t, ray->direction));
    height_proj = dot_product(v_sub(coll_point, cy->location), cy->orientation);
    if (height_proj < -cy->height / 2 || height_proj > cy->height / 2)
        return (check_caps(ray, cy)); // if it would hit curved part but curved part is not that long, check if it hits a cap

    update_ray(ray, cy, t);
	ray->coll_norm = compute_normal_curved(ray->end, cy);
	// check if cap is closer than curved part
	check_caps(ray, cy);
    return (HIT);
}

