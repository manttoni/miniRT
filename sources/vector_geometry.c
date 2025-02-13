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

double	v_dist(t_vector a, t_vector b)
{
	return (v_len(v_sub(a, b)));
}

t_vector	normalize_vector(t_vector v)
{
	double	len;

	len = v_len(v);
	return ((t_vector){v.x / len, v.y / len, v.z / len});
}
