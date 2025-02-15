#include "../includes/minirt.h"

void	rotate_object(t_object *object, t_vector new_orientation)
{
	object->orientation = normalize_vector(new_orientation);
	print_vector(object->orientation);
}

void	translate_object(t_object *object, t_vector delta)
{
	object->location = v_sum(object->location, delta);
	print_vector(object->location);
}

// Rodrigues' rotation formula
// Function to rotate a vector v around an arbitrary axis k by angle theta
void rotate_vector(t_vector *v, t_vector k, float theta) {
    printf("Rotating vector: ");
    print_vector(*v);
    printf("Around vector: ");
    print_vector(k);
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    // Ensure k is a unit vector
    k = normalize_vector(k);

    // Compute dot product k . v
    float dot_kv = dot_product(k, *v);

    // Compute cross product k x v
    t_vector cross_kv = cross_product(k, *v);

    // Compute rotated vector using Rodrigues' formula
    v->x = v->x * cosTheta + cross_kv.x * sinTheta + k.x * dot_kv * (1 - cosTheta);
    v->y = v->y * cosTheta + cross_kv.y * sinTheta + k.y * dot_kv * (1 - cosTheta);
    v->z = v->z * cosTheta + cross_kv.z * sinTheta + k.z * dot_kv * (1 - cosTheta);
}