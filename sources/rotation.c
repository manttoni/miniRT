#include "../includes/minirt.h"

// Function to rotate a vector around the X-axis
t_vector rotate_vector_x(t_vector v, float theta) {
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    // Rotation matrix for the X-axis
    float rotationMatrix[3][3] = {
        {1, 0, 0},
        {0, cosTheta, -sinTheta},
        {0, sinTheta, cosTheta}
    };

    // Perform the matrix multiplication: result = rotationMatrix * v
    t_vector result;
    result.x = rotationMatrix[0][0] * v.x + rotationMatrix[0][1] * v.y + rotationMatrix[0][2] * v.z;
    result.y = rotationMatrix[1][0] * v.x + rotationMatrix[1][1] * v.y + rotationMatrix[1][2] * v.z;
    result.z = rotationMatrix[2][0] * v.x + rotationMatrix[2][1] * v.y + rotationMatrix[2][2] * v.z;

    return normalize_vector(result);
}

// Function to rotate a vector around the Y-axis
t_vector rotate_vector_y(t_vector v, float theta) {
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    // Rotation matrix for the Y-axis
    float rotationMatrix[3][3] = {
        {cosTheta, 0, sinTheta},
        {0, 1, 0},
        {-sinTheta, 0, cosTheta}
    };

    // Perform the matrix multiplication: result = rotationMatrix * v
    t_vector result;
    result.x = rotationMatrix[0][0] * v.x + rotationMatrix[0][1] * v.y + rotationMatrix[0][2] * v.z;
    result.y = rotationMatrix[1][0] * v.x + rotationMatrix[1][1] * v.y + rotationMatrix[1][2] * v.z;
    result.z = rotationMatrix[2][0] * v.x + rotationMatrix[2][1] * v.y + rotationMatrix[2][2] * v.z;

    return normalize_vector(result);
}

// Function to rotate a vector around the Z-axis
t_vector rotate_vector_z(t_vector v, float theta) {
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    // Rotation matrix for the Z-axis
    float rotationMatrix[3][3] = {
        {cosTheta, -sinTheta, 0},
        {sinTheta, cosTheta, 0},
        {0, 0, 1}
    };

    // Perform the matrix multiplication: result = rotationMatrix * v
    t_vector result;
    result.x = rotationMatrix[0][0] * v.x + rotationMatrix[0][1] * v.y + rotationMatrix[0][2] * v.z;
    result.y = rotationMatrix[1][0] * v.x + rotationMatrix[1][1] * v.y + rotationMatrix[1][2] * v.z;
    result.z = rotationMatrix[2][0] * v.x + rotationMatrix[2][1] * v.y + rotationMatrix[2][2] * v.z;

    return normalize_vector(result);
}
