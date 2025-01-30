#include "../includes/minirt.h"

/**
 * v_len - Computes the magnitude (length) of a vector.
 * @v: The input vector.
 *
 * This function:
 * - Uses the Euclidean norm formula:
 *   \f$ |v| = \sqrt{x^2 + y^2 + z^2} \f$
 *
 * Return:
 * - The **length** (magnitude) of the vector.
 */
double	v_len(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/**
 * v_angle - Computes the angle (in radians) between two vectors.
 * @a: First vector.
 * @b: Second vector.
 *
 * This function:
 * - Uses the **dot product formula** to compute the cosine of the angle:
 *   \f$ \cos(\theta) = \frac{a \cdot b}{|a| |b|} \f$
 * - Uses `acos()` to get the actual angle in **radians**.
 * - Clamps values to **avoid floating-point errors**.
 *
 * Return:
 * - The **angle in radians** between the vectors.
 */
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

/**
 * normalize_vector - Returns a unit vector (length = 1) in the same direction.
 * @v: The input vector.
 *
 * This function:
 * - Computes the **normalized unit vector** using:
 *   \f$ v_{normalized} = \frac{v}{|v|} \f$
 * - Prevents division by zero.
 *
 * Return:
 * - A **unit vector** pointing in the same direction as `v`.
 */
t_vector	normalize_vector(t_vector v)
{
	double	len;

	len = v_len(v);
	return (t_vector){v.x / len, v.y / len, v.z / len};
}

/**
 * dot_product - Computes the dot product of two vectors.
 * @v1: First vector.
 * @v2: Second vector.
 *
 * This function:
 * - Uses the **dot product formula**:
 *   \f$ v_1 \cdot v_2 = x_1x_2 + y_1y_2 + z_1z_2 \f$
 *
 * Return:
 * - The **dot product value**.
 */
double	dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/**
 * cross_product - Computes the cross product of two vectors.
 * @v1: First vector.
 * @v2: Second vector.
 *
 * This function:
 * - Uses the **cross product formula**:
 *   \f$ v_1 \times v_2 = (y_1z_2 - z_1y_2, z_1x_2 - x_1z_2, x_1y_2 - y_1x_2) \f$
 * - Returns a **vector perpendicular** to both input vectors.
 *
 * Return:
 * - The **cross product vector**.
 */
t_vector	cross_product(t_vector v1, t_vector v2)
{
	t_vector	product;

	product.x = v1.y * v2.z - v1.z * v2.y;
	product.y = v1.z * v2.x - v1.x * v2.z;
	product.z = v1.x * v2.y - v1.y * v2.x;
	return (product);
}

/**
 * print_vector - Prints a vector's components and length.
 * @v: The vector to print.
 */
void	print_vector(t_vector v)
{
	printf("x: %1.2f, y: %1.2f, z: %1.2f, len: %1.2f\n", v.x, v.y, v.z, v_len(v));
}

/**
 * vector - Creates a vector with given coordinates.
 * @x: X component.
 * @y: Y component.
 * @z: Z component.
 *
 * Return:
 * - A `t_vector` structure.
 */
t_vector	vector(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

/**
 * v_mul - Multiplies a vector by a scalar.
 * @t: The scalar value.
 * @v: The vector.
 */
t_vector	v_mul(double t, t_vector v)
{
	t_vector	product;

	product.x = v.x * t;
	product.y = v.y * t;
	product.z = v.z * t;
	return (product);
}

/**
 * v_sub - Computes the difference of two vectors.
 * @v1: First vector.
 * @v2: Second vector.
 */
t_vector	v_sub(t_vector v1, t_vector v2)
{
	t_vector	difference;

	difference.x = v1.x - v2.x;
	difference.y = v1.y - v2.y;
	difference.z = v1.z - v2.z;
	return (difference);
}

/**
 * v_sum - Computes the sum of two vectors.
 * @v1: First vector.
 * @v2: Second vector.
 */
t_vector	v_sum(t_vector v1, t_vector v2)
{
	t_vector	sum;

	sum.x = v1.x + v2.x;
	sum.y = v1.y + v2.y;
	sum.z = v1.z + v2.z;
	return (sum);
}

/**
 * v_dist - Computes the Euclidean distance between two points (vectors).
 * @a: The first vector (point A).
 * @b: The second vector (point B).
 *
 * This function:
 * - Computes the **difference vector** between `a` and `b` using `v_sub(a, b)`.
 * - Computes the **length (magnitude)** of this difference vector using `v_len()`.
 * - Uses the **Euclidean distance formula**:
 *   \[
 *   d = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2 + (z_2 - z_1)^2}
 *   \]
 *
 * Return:
 * - The **distance** between the two points.
 */
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
