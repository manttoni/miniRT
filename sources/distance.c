
#include "../includes/minirt.h"

double  sphere_distance(t_vector point, t_object *sphere)
{
    return (v_dist(sphere->location, point) - sphere->diameter / 2);
}

double  plane_distance(t_vector point, t_object *plane)
{
    return (fabs(dot_product(plane->orientation, point) + plane->d));
}

double  closest(t_ray *ray, t_object *objects)
{
    double  dist;
    double  closest_dist;

    closest_dist = RENDER_DISTANCE;
    while (objects)
    {
        if (objects->type == SPHERE)
            dist = sphere_distance(ray->location, objects);
        else if (objects->type == PLANE)
            dist = plane_distance(ray->location, objects);
        else
            dist = closest_dist + 1;
        if (dist < closest_dist)
        {
            ray->color = objects->color;
            closest_dist = dist;
        }
        objects = objects->next;
    }
    return closest_dist;
}
