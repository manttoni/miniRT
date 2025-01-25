#include "../includes/vector.h"
#include "../includes/object.h"
#include "../includes/defines.h"

double  sphere_distance(t_vector point, t_object *sphere)
{
    return (vector_len(vector_substract(sphere->location, point)) - sphere->diameter / 2);
}

double  plane_distance(t_vector point, t_object *plane)
{
    double d;
    
    d = dot_product(plane->orientation, plane->location);
    return (fabs(dot_product(plane->orientation, point) + d));
}

double  closest(t_ray *ray, t_node *objects)
{
    double  dist;
    double  closest_dist;
    t_object    *o;

    closest_dist = RENDER_DISTANCE;
    while (objects)
    {
        o = (t_object *) objects->data;
        if (o->type == SPHERE)
            dist = sphere_distance(ray->location, o);
        else if (o->type == PLANE)
            dist = plane_distance(ray->location, o);
        else
            dist = closest_dist + 1;
        if (dist < closest_dist)
        {
            ray->color = o->color;
            closest_dist = dist;
        }
        objects = objects->next;
    }
    return closest_dist;
}