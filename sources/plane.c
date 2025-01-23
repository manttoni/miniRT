#include "../includes/minirt.h"

int scale_color(int color, double intensity)
{
    int r = ((color >> 16) & 0xFF) * intensity;
    int g = ((color >> 8) & 0xFF) * intensity;
    int b = (color & 0xFF) * intensity;

    return ((r << 16) | (g << 8) | b);
}

//int     shade_pixel;

double  calcD(t_object *plane)
{
    double  d;

    d = -dot_product(plane->orientation, plane->location);
    return (d);
}

int plane_collision(t_ray *ray, t_object *plane)
{
    double  denominator;
    double  numerator;
    t_vector intersection;
    double  t;

    denominator = dot_product(plane->orientation, ray->direction);
    if (denominator == 0.0)
        return 0;
    numerator = -dot_product(plane->orientation, ray->start) + calcD(plane);
    t = numerator / denominator;

    intersection.x = ray->start.x + t * ray->direction.x;
    intersection.y = ray->start.y + t * ray->direction.y;
    intersection.z = ray->start.z + t * ray->direction.z;
    if (ray->distance > t)
    {
        ray->distance = t;
        ray->color = plane->color;
    }
    return (1);
}
