#include "../includes/minirt.h"

static void    set_coll_norm(t_ray *ray, t_object *object)
{
    if (object->type == SPHERE)
        ray->coll_norm = normalize_vector(v_sub(object->location, ray->end));
    else if (object->type == PLANE)
        ray->coll_norm = object->orientation;
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

	oc = v_sub(ray->start, sp->location);  // Vector from ray origin to sphere center
	a = dot_product(ray->direction, ray->direction);
	b = 2 * dot_product(ray->direction, oc);  
	c = dot_product(oc, oc) - (sp->diameter / 2) * (sp->diameter / 2);

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0); // No intersection

	t1 = (-b - sqrt(discriminant)) / (2 * a); // First intersection
	t2 = (-b + sqrt(discriminant)) / (2 * a); // Second intersection

    // If both t1 and t2 are negative, the sphere is behind the ray
	if (t1 < 0 && t2 < 0)
		return (0);

	double t = (t1 > 0) ? t1 : t2; // Choose the closest valid intersection

	if (t < ray->distance) // Update only if it's a closer intersection
	{
		ray->color = sp->color;
		ray->distance = t;
		ray->end = v_sum(ray->start, v_mul(ray->distance, ray->direction));
		set_coll_norm(ray, sp);
		return (1);
	}

	return (0);
}


int plane_collision(t_ray *ray, t_object *pl)
{
    double denominator;
    double numerator;
    double t;
    
    denominator = dot_product(pl->orientation, ray->direction);
    if (fabs(denominator) < EPSILON) // Prevent division by zero
        return 0;

    t_vector plane_to_ray = v_sub(pl->location, ray->start);
    numerator = dot_product(pl->orientation, plane_to_ray);
    t = numerator / denominator;

    if (t < 0 || t >= ray->distance) // Ignore negative or farther intersections
        return 0;

    // Update ray intersection
    ray->coll_norm = pl->orientation;
    ray->distance = t;
    ray->end = v_sum(ray->start, v_mul(t, ray->direction));
    ray->color = pl->color;

    return 1;
}
