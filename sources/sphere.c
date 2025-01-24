#include "../includes/minirt.h"


int sphere_collision(t_ray *ray, t_object *sphere)
{
    double a, b, c, discriminant, t1, t2;
    t_vector oc = vector_substract(ray->start, sphere->location); // Vector from ray start to sphere center

    // Coefficients of the quadratic equation
    a = dot_product(ray->direction, ray->direction);
    b = 2 * dot_product(oc, ray->direction); // Correct sign for b
    c = dot_product(oc, oc) - pow(sphere->diameter / 2, 2);

    // Calculate the discriminant
    discriminant = b * b - 4 * a * c;

    // Compute surface normal
    N = normalize_vector(vector_substract(P, sphere_center));

    // Compute light direction
    L = normalize_vector(vector_substract(light_pos, P));

    // Compute diffuse intensity (clamped to [0, 1])
    diffuse_intensity = fmax(0, dot_product(N, L));

    // Scale the base color by the diffuse intensity
    return (scale_color(base_color, diffuse_intensity));
}*/

int sphere_collision(t_ray *ray, t_object *sphere)
{
    double a, b, c, discriminant, t1, t2;
    t_vector    intersection;
    t_vector oc = vector_substract(ray->start, sphere->location); // Vector from ray start to sphere center

    // Coefficients of the quadratic equation
    a = dot_product(ray->direction, ray->direction);
    b = 2 * dot_product(oc, ray->direction); // Correct sign for b
    c = dot_product(oc, oc) - pow(sphere->diameter / 2, 2);

    // Calculate the discriminant
    discriminant = b * b - 4 * a * c;

    // No intersection if the discriminant is negative
    if (discriminant < 0)
    {
        return (0);
    }

    // Calculate both intersection points
    t1 = (-b - sqrt(discriminant)) / (2 * a);
    t2 = (-b + sqrt(discriminant)) / (2 * a);

    // Find the closest positive intersection point
    double t_closest = -1;
    if (t1 > 0 && (t_closest < 0 || t1 < t_closest))
        t_closest = t1;
    if (t2 > 0 && (t_closest < 0 || t2 < t_closest))
        t_closest = t2;

    // If no positive intersection points are found, return 0
    if (t_closest < 0)
        return (0);

    if (t_closest < 0)
        return 0;
    // Update ray properties if the intersection is closer than the current ray distance
    if (fabs(t_closest) < ray->distance)
    {
        intersection = vector_sum(ray->start, vector_multiply(t_closest, ray->direction));
        ray->distance = fabs(t_closest);
        ray->color = sphere->color;
        ray->coll_norm = normalize_vector(vector_substract(intersection, sphere->location));
        //printf("Ray hit the sphere!\n");
    }
    //printf("Collision at distance: %f\n", ray->distance);
    return (1);
}

