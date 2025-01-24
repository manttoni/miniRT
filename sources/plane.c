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
    double  t;

    denominator = dot_product(plane->orientation, ray->direction);
    if (denominator == 0.0)
        return 0;
    numerator = -dot_product(plane->orientation, ray->start) + calcD(plane);
    t = numerator / denominator;
    if (t > 0)
        return 0;
    if (ray->distance > fabs(t))
    {
        ray->distance = fabs(t);
        //ray->color = plane->color;
        // for testing
        t_vector P;
        P = vector_sum(ray->start, vector_multiply(t, ray->direction));
        int checker_size = 100;  // Size of one square in the checkerboard pattern
        int x_check = (int)floor(P.x / checker_size) % 2;
        int y_check = (int)floor(P.y / checker_size) % 2;

        // XOR to create alternating pattern
        if ((x_check + y_check) % 2 == 0) {
            // Color 1 (e.g., white)
            ray->color = 0xffffffff;
        } else {
            // Color 2 (e.g., black)
            ray->color = 0xff000;
        }
    }
    //printf("Collision at distance: %f\n", ray->distance);
    return (1);
}
