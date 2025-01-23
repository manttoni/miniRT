#include "../inc/minirt.h"

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

int plane_collision(t_vector linePoint, 
                    t_vector lineDir, 
                    t_object plane, 
                    t_vector *intersection)
{
    double  denominator;
    double  numerator;
    double  t;

    denominator = dot_product(plane->orientation, lineDir);
    if (denominator == 0.0)
        return 0;
    numerator = -dot_product(plane->orientation, linePoint) + calcD(plane);
    t = numerator / denominator;

    intersection->x = linePoint.x + t * lineDir.x;
    intersection->y = linePoint.y + t * lineDir.y;
    intersection->z = linePoint.z + t * lineDir.z;

    return (1);
}
