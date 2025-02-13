#include "../includes/minirt.h"

static void	update_ray(t_ray *ray, t_object *object, double t)
{
	if (t >= ray->distance)
		return ;
	ray->color = object->color;
	ray->distance = t;
	ray->end = v_sum(ray->start, v_mul(ray->distance, ray->direction));
	if (object->type == SPHERE)
		ray->coll_norm = normalize_vector(v_sub(ray->end, object->location));
	if (object->type == PLANE)
		ray->coll_norm = object->orientation;
	ray->object = object;
}

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

double calc_t(double *t, t_vector v1, t_vector v2, double r)
{
	double	t1;
	double	t2;
	t_disc	disc;

	*t = -1;
	disc.a = dot_product(v1, v1);
	disc.b = 2 * dot_product(v1, v2);
	disc.c = dot_product(v2, v2) - r * r;
	disc.discriminant = disc.b * disc.b - 4 * disc.a * disc.c;
	if (disc.discriminant < 0)
		return (FAILURE);
	t1 = (-disc.b - sqrt(disc.discriminant)) / (2 * disc.a);
	t2 = (-disc.b + sqrt(disc.discriminant)) / (2 * disc.a);
	if (t1 < 0 && t2 < 0)
		return (FAILURE);
	if (t1 > 0)
		*t = t1;
	else
		*t = t2;
	return (SUCCESS);
}

int	sphere_collision(t_ray *ray, t_object *sp)
{
	t_vector	oc;
	double		t;

	oc = v_sub(ray->start, sp->location);
	if (calc_t(&t, ray->direction, oc, sp->diameter / 2) == FAILURE)
		return (NO_HIT);
	if (t >= ray->distance)
		return (NO_HIT);
	update_ray(ray, sp, t);
	return (HIT);
}

t_vector compute_normal_curved(t_vector collision_point, t_object *cy)
{
	t_vector to_point;
	t_vector projection;
	t_vector normal;

    to_point = v_sub(collision_point, cy->location);
    projection = v_mul(dot_product(to_point, cy->orientation), cy->orientation);
    normal = v_sub(to_point, projection);
    return (normalize_vector(normal));
}

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
			ray->coll_norm = cap_normal;
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

	if (calc_t(&t, proj_dir, oc_proj, cy->diameter / 2) == FAILURE)
		return (check_caps(ray, cy));

    coll_point = v_sum(ray->start, v_mul(t, ray->direction));
    height_proj = dot_product(v_sub(coll_point, cy->location), cy->orientation);
    if (fabs(height_proj) > cy->height / 2)
        return (check_caps(ray, cy));
	if (t > ray->distance)
		return (check_caps(ray, cy));
    update_ray(ray, cy, t);
	ray->coll_norm = compute_normal_curved(ray->end, cy);
	check_caps(ray, cy);
    return (HIT);
}

