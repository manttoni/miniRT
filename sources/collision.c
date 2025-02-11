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
	if (object->type == CYLINDER)
		ray->coll_norm = vector(0,1,0);
	ray->object = object;
}

/*	numerator is a precalculated value stored in t_object */
int plane_collision(t_ray *ray, t_object *pl)
{
	double denominator;
	double t;

	denominator = dot_product(pl->orientation, ray->direction);
	if (fabs(denominator) < EPSILON)
		return (NO_HIT);
	t = pl->numerator / denominator;
	if (t < EPSILON || t >= ray->distance)
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

// Function to check if the ray intersects a cylinder's cap
int cap_collision(t_ray *ray, t_object *cy, int cap_side) {
    t_vector cap_center, cap_normal, intersection_point;
    double t;

    // Set the normal depending on which cap (top or bottom)
    cap_normal = cy->orientation; // top cap: same as cylinder orientation
    if (cap_side == BOTTOM_CYLINDER_CAP) {
        cap_normal = v_mul(-1, cy->orientation); // bottom cap: opposite of cylinder orientation
    }

    // Set the cap center based on whether it's the top or bottom cap
    cap_center = v_sum(cy->location, v_mul(cap_side == TOP_CYLINDER_CAP ? cy->height / 2 : -cy->height / 2, cy->orientation));

    // Calculate intersection with the plane of the cap
    double denom = dot_product(ray->direction, cap_normal);
    if (fabs(denom) < EPSILON) {
        return NO_HIT; // The ray is parallel to the cap, no intersection
    }

    t = dot_product(v_sub(cap_center, ray->start), cap_normal) / denom;

    if (t < 0 || t >= ray->distance) {
        return NO_HIT; // The intersection occurs behind the ray's origin or beyond the ray's distance
    }

    // Calculate the intersection point
    intersection_point = v_sum(ray->start, v_mul(t, ray->direction));

    // Check if the intersection point is within the cap's radius
    if (dot_product(v_sub(intersection_point, cap_center), v_sub(intersection_point, cap_center)) <= (cy->diameter / 2) * (cy->diameter / 2)) {
        update_ray(ray, cy, t);
		return HIT;
    }

    return NO_HIT;
}


int	cylinder_collision(t_ray *ray, t_object *cy)
{
	t_vector	oc, proj_dir, oc_proj, coll_point;
	double		a, b, c, discriminant, t1, t2, t;
	double		height_proj;
	
	// Vector from cylinder center to ray origin
	oc = v_sub(ray->start, cy->location);

	// Project ray direction and oc onto the plane perpendicular to cylinder axis
	proj_dir = v_sub(ray->direction, v_mul(dot_product(ray->direction, cy->orientation), cy->orientation));
	oc_proj = v_sub(oc, v_mul(dot_product(oc, cy->orientation), cy->orientation));

	// Solve quadratic equation for curved surface intersection
	a = dot_product(proj_dir, proj_dir);
	b = 2 * dot_product(proj_dir, oc_proj);
	c = dot_product(oc_proj, oc_proj) - (cy->diameter / 2) * (cy->diameter / 2);
	discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (NO_HIT);

	// Find closest valid intersection
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	t = (t1 > 0) ? t1 : t2;
	if (t < 0 || t >= ray->distance)
		return (NO_HIT);

	// Compute collision point
	coll_point = v_sum(ray->start, v_mul(t, ray->direction));

	// Check if inside cylinder height range
	height_proj = dot_product(v_sub(coll_point, cy->location), cy->orientation);
	if (height_proj < -cy->height / 2 || height_proj > cy->height / 2)
		return (NO_HIT);

	if (cap_collision(ray, cy, TOP_CYLINDER_CAP) == HIT && ray->distance < t)
		return (HIT);
	if (cap_collision(ray, cy, BOTTOM_CYLINDER_CAP) == HIT && ray->distance < t)
    	return (HIT);

	// Update ray with collision data
	update_ray(ray, cy, t);
	return (HIT);
}
