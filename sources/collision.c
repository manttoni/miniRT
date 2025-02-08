#include "../includes/minirt.h"

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
		return (0);
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t1 < 0 && t2 < 0)
		return (0);
	double t = (t1 > 0) ? t1 : t2;
	if (t < ray->distance)
	{
		ray->color = sp->color;
		ray->distance = t;
		ray->end = v_sum(ray->start, v_mul(ray->distance, ray->direction));
		ray->coll_norm = normalize_vector(v_sub(ray->end, sp->location));
		ray->object = sp;
		return (1);
	}

	return (0);
}

/*	numerator is a precalculated value stored in t_object */
int plane_collision(t_ray *ray, t_object *pl)
{
	double denominator;
	double t;

	denominator = dot_product(pl->orientation, ray->direction);
	if (fabs(denominator) < EPSILON)
		return (0);
	t = pl->numerator / denominator;
	if (t < EPSILON || t >= ray->distance)
		return (0);
	ray->distance = t;
	ray->end = v_sum(ray->start, v_mul(t, ray->direction));
	ray->color = pl->color;
	ray->coll_norm = pl->orientation;
	ray->object = pl;
	return (1);
}
