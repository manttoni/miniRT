#include "../includes/minirt.h"

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


// // Function to rotate a vector around the X-axis
// t_vector rotate_vector_x(t_vector v, float theta) {
// float cosTheta = cos(theta);
// float sinTheta = sin(theta);

// // Rotation matrix for the X-axis
// float rotationMatrix[3][3] = {
//     {1, 0, 0},
//     {0, cosTheta, -sinTheta},
//     {0, sinTheta, cosTheta}
// };

// // Perform the matrix multiplication: result = rotationMatrix * v
// t_vector result;
// result.x = rotationMatrix[0][0] * v.x + rotationMatrix[0][1] * v.y + rotationMatrix[0][2] * v.z;
// result.y = rotationMatrix[1][0] * v.x + rotationMatrix[1][1] * v.y + rotationMatrix[1][2] * v.z;
// result.z = rotationMatrix[2][0] * v.x + rotationMatrix[2][1] * v.y + rotationMatrix[2][2] * v.z;

// return normalize_vector(result);
// }

// // Function to rotate a vector around the Y-axis
// t_vector rotate_vector_y(t_vector v, float theta) {
// float cosTheta = cos(theta);
// float sinTheta = sin(theta);

// // Rotation matrix for the Y-axis
// float rotationMatrix[3][3] = {
//     {cosTheta, 0, sinTheta},
//     {0, 1, 0},
//     {-sinTheta, 0, cosTheta}
// };

// // Perform the matrix multiplication: result = rotationMatrix * v
// t_vector result;
// result.x = rotationMatrix[0][0] * v.x + rotationMatrix[0][1] * v.y + rotationMatrix[0][2] * v.z;
// result.y = rotationMatrix[1][0] * v.x + rotationMatrix[1][1] * v.y + rotationMatrix[1][2] * v.z;
// result.z = rotationMatrix[2][0] * v.x + rotationMatrix[2][1] * v.y + rotationMatrix[2][2] * v.z;

// return normalize_vector(result);
// }

// // Function to rotate a vector around the Z-axis
// t_vector rotate_vector_z(t_vector v, float theta) {
// float cosTheta = cos(theta);
// float sinTheta = sin(theta);

// // Rotation matrix for the Z-axis
// float rotationMatrix[3][3] = {
//     {cosTheta, -sinTheta, 0},
//     {sinTheta, cosTheta, 0},
//     {0, 0, 1}
// };

// // Perform the matrix multiplication: result = rotationMatrix * v
// t_vector result;
// result.x = rotationMatrix[0][0] * v.x + rotationMatrix[0][1] * v.y + rotationMatrix[0][2] * v.z;
// result.y = rotationMatrix[1][0] * v.x + rotationMatrix[1][1] * v.y + rotationMatrix[1][2] * v.z;
// result.z = rotationMatrix[2][0] * v.x + rotationMatrix[2][1] * v.y + rotationMatrix[2][2] * v.z;

// return normalize_vector(result);
// }
