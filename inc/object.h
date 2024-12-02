#ifndef OBJECT_H
# define OBJECT_H

# include "../inc/vector.h"

typedef struct	s_sphere
{
	t_vector	center;
	double		diameter;
	int			color;
}	t_sphere;

t_sphere	*create_sphere(t_vector center, double diameter, int color);
int			sphere_collision(t_vector d, t_sphere *sphere);

#endif
