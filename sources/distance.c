
#include "../includes/minirt.h"

double  sphere_distance(t_vector point, t_object *sphere)
{
    return (v_dist(sphere->location, point) - sphere->diameter / 2);
}

double  plane_distance(t_vector point, t_object *plane)
{
    return (fabs(dot_product(plane->orientation, point) + plane->d));
}

static void    set_coll_norm(t_ray *ray, t_object *object)
{
    if (object->type == SPHERE)
        ray->coll_norm = normalize_vector(v_sub(object->location, ray->location));
    else if (object->type == PLANE)
        ray->coll_norm = object->orientation;
}

double  closest(t_ray *ray, t_object **arr)
{
    double  dist;
    double  closest_dist;
    size_t  i;

    i = 0;
    closest_dist = RENDER_DISTANCE;
    while (arr[i] != NULL)
    {
        if (arr[i]->sdf != NULL)
            dist = (*arr[i]->sdf)(ray->location, arr[i]);
        // if (arr[i]->type == SPHERE)
        //     dist = sphere_distance(ray->location, arr[i]);
        // else if (arr[i]->type == PLANE)
        //     dist = plane_distance(ray->location, arr[i]);
        else
            dist = closest_dist + 1;
        if (dist < closest_dist)
        {
            ray->color = arr[i]->color;
            closest_dist = dist;
            set_coll_norm(ray, arr[i]);
        }
        i++;
    }
    return (closest_dist);
}
