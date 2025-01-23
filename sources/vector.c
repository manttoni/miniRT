#include "../includes/vector.h"
#include <stdio.h>

double	vector_len(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	normalize_vector(t_vector v)
{
	double	len;

	len = vector_len(v);
	return (t_vector){v.x / len, v.y / len, v.z / len};
}

double	dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	cross_product(t_vector v1, t_vector v2)
{
	t_vector	product;

	product.x = v1.y * v2.z - v1.z * v2.y;
	product.y = v1.z * v2.x - v1.x * v2.z;
	product.z = v1.x * v2.y - v1.y * v2.x;
	return (product);
}

void	print_vector(t_vector v)
{
	printf("x: %f, y: %f, z: %f, len: %f\n", v.x, v.y, v.z, vector_len(v));
}

t_vector	vector(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vector	vector_multiply(double t, t_vector v)
{
	t_vector	product;

	product.x = v.x * t;
	product.y = v.y * t;
	product.z = v.z * t;
	return (product);
}

t_vector	vector_substract(t_vector v1, t_vector v2)
{
	t_vector	difference;

	difference.x = v1.x - v2.x;
	difference.y = v1.y - v2.y;
	difference.z = v1.z - v2.z;
	return (difference);
}

t_vector	vector_sum(t_vector v1, t_vector v2)
{
	t_vector	sum;

	sum.x = v1.x + v2.x;
	sum.y = v1.y + v2.y;
	sum.z = v1.z + v2.z;
	return (sum);
}

/*
int main(void)
{
	t_vector v = (t_vector){1, 1, 1};
	t_vector v2 = (t_vector){-1, 1, 0};
	t_vector vn = normalize_vector(v);
	printf("v:\n");
	print_vector(v);
	printf("normalized v:\n");
	print_vector(vn);
	printf("cross product of\n");
	print_vector(v);
	print_vector(v2);
	print_vector(cross_product(v, v2));

	return (0);
}
*/
