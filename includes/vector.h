#ifndef VECTOR_H
# define VECTOR_H

// # include "./minirt.h"
# include <math.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

double		v_angle(t_vector a, t_vector b);
double		v_len(t_vector v);
t_vector	normalize_vector(t_vector v);
t_vector	cross_product(t_vector v1, t_vector v2);
double		dot_product(t_vector v1, t_vector v2);
t_vector	v_sum(t_vector v1, t_vector v2);
t_vector	v_sub(t_vector v1, t_vector v2);
t_vector	v_mul(double t, t_vector v);
void		print_vector(t_vector v);
t_vector	vector(double x, double y, double z);
double		v_dist(t_vector a, t_vector b);

#endif
