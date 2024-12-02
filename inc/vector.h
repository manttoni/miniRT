#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

double		vector_len(t_vector v);
t_vector	normalize_vector(t_vector v);
t_vector	cross_product(t_vector v1, t_vector v2);
double		dot_product(t_vector v1, t_vector v2);
void		print_vector(t_vector v);
t_vector	vector(double x, double y, double z);

#endif
