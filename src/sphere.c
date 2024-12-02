#include "../inc/minirt.h"

t_sphere	*create_sphere(t_vector center, double diameter, int color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->center = center;
	sphere->diameter = diameter;
	sphere->color = color;
	return (sphere);
}

int	sphere_collision(t_vector d, t_sphere *sphere)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = dot_product(d, d);
	b = -2 * dot_product(d, sphere->center);
	c = dot_product(sphere->center, sphere->center) - sphere->diameter / 2 * sphere->diameter / 2;
	discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (BACKGROUND_COLOR);
	return (sphere->color);
}
