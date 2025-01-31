#include "../includes/minirt.h"

/* if ray collides with sp, ray updates its variables 
    and func returns 1, otherwise 0*/
int sphere_collision(t_ray *ray, t_object *sp)
{
    (void) ray;
    (void) sp;
    return 0;
}

int plane_collision(t_ray *ray, t_object *pl)
{
    double  denominator;
    double  numerator;
    double  t;

    denominator = dot_product(pl->orientation, ray->direction);
    if (denominator == 0.0)
        return 0;
    numerator = -dot_product(pl->orientation, ray->start) + pl->d;
    t = numerator / denominator;

    if (ray->distance > t)
    {
        ray->coll_norm = pl->orientation;
        ray->distance = t;
        ray->end = v_sum(ray->start, v_mul(t, ray->direction));
        ray->color = pl->color;
    }
    return (1);
}