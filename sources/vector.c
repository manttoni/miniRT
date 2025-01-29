#include "../includes/minirt.h"

double	v_len(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	v_angle(t_vector a, t_vector b)
{
	double	dot;
	double	cos_theta;

	dot = dot_product(a, b);
	cos_theta = dot / (v_len(a) * v_len(b));
	if (cos_theta > 1.0)
		cos_theta = 1.0;
    if (cos_theta < -1.0)
		cos_theta = -1.0;
	return (acos(cos_theta));
}

t_vector	normalize_vector(t_vector v)
{
	double	len;

	len = v_len(v);
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
	printf("x: %1.2f, y: %1.2f, z: %1.2f, len: %1.2f\n", v.x, v.y, v.z, v_len(v));
}

t_vector	vector(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vector	v_mul(double t, t_vector v)
{
	t_vector	product;

	product.x = v.x * t;
	product.y = v.y * t;
	product.z = v.z * t;
	return (product);
}

t_vector	v_sub(t_vector v1, t_vector v2)
{
	t_vector	difference;

	difference.x = v1.x - v2.x;
	difference.y = v1.y - v2.y;
	difference.z = v1.z - v2.z;
	return (difference);
}

t_vector	v_sum(t_vector v1, t_vector v2)
{
	t_vector	sum;

	sum.x = v1.x + v2.x;
	sum.y = v1.y + v2.y;
	sum.z = v1.z + v2.z;
	return (sum);
}

double	v_dist(t_vector a, t_vector b)
{
	return (v_len(v_sub(a, b)));
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
