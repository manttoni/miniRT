#include "../inc/minirt.h"

int scale_color(int color, double intensity)
{
    int r = ((color >> 16) & 0xFF) * intensity;
    int g = ((color >> 8) & 0xFF) * intensity;
    int b = (color & 0xFF) * intensity;

    return ((r << 16) | (g << 8) | b);
}

int     shade_pixel(t_vector P, t_vector light_pos, t_vector sphere_center, int base_color)
{
    t_vector    N; // Surface normal
    t_vector    L; // Light direction
    double      diffuse_intensity;

    // Compute surface normal
    N = normalize_vector(vector_substract(P, sphere_center));

    // Compute light direction
    L = normalize_vector(vector_substract(light_pos, P));

    // Compute diffuse intensity (clamped to [0, 1])
    diffuse_intensity = fmax(0, dot_product(N, L));

    // Scale the base color by the diffuse intensity
    return (scale_color(base_color, diffuse_intensity));
}

int	sphere_collision(t_vector d, t_object *sphere, double *distance)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;

	a = dot_product(d, d);
	b = -2 * dot_product(d, sphere->location);
	c = dot_product(sphere->location, sphere->location) - sphere->diameter / 2 * sphere->diameter / 2;
	discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (BACKGROUND_COLOR);
    t1 = (-b - sqrt(discriminant)) / (2 * a); // First intersection
    t2 = (-b + sqrt(discriminant)) / (2 * a); // Second intersection
	*distance = fmin(*distance, fmin(t1, t2));
	return (shade_pixel(vector_multiply(fmin(t1, t2), d), vector(50, 0, 50), sphere->location, sphere->color));
}
