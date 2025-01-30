
#include "../includes/minirt.h"

/**
 * sphere_distance - Computes the signed distance from a point to a sphere.
 * @point: The point in space from which the distance is measured.
 * @sphere: The sphere object containing its center location and diameter.
 *
 * This function calculates the **Signed Distance Function (SDF)** for a sphere:
 * - `v_dist(sphere->location, point)` gives the Euclidean distance from the point to the sphere center.
 * - The sphere's **radius** is subtracted (`diameter / 2`) to get the **actual surface distance**.
 *
 * If the distance is:
 * - **Positive** → The point is outside the sphere.
 * - **Zero** → The point is on the surface.
 * - **Negative** → The point is inside the sphere.
 *
 * Return: The signed distance to the sphere's surface.
 */
double  sphere_distance(t_vector point, t_object *sphere)
{
    return (v_dist(sphere->location, point) - sphere->diameter / 2);
}

/**
 * plane_distance - Computes the signed distance from a point to a plane.
 * @point: The point in space from which the distance is measured.
 * @plane: The plane object containing its normal vector and plane constant `d`.
 *
 * This function calculates the **Signed Distance Function (SDF)** for a plane:
 * - The equation of a plane is: `Ax + By + Cz + d = 0`
 * - The signed distance from any point to the plane is:
 *   **`fabs(dot_product(plane->orientation, point) + plane->d)`**
 *
 * If the distance is:
 * - **Positive** → The point is above the plane.
 * - **Zero** → The point is on the plane.
 * - **Negative** → The point is below the plane.
 *
 * Return: The absolute signed distance to the plane.
 */
double  plane_distance(t_vector point, t_object *plane)
{
    return (fabs(dot_product(plane->orientation, point) + plane->d));
}

/**
 * closest - Finds the closest object intersected by the ray.
 * @ray: Pointer to the ray being traced.
 * @objects: List of objects in the scene.
 *
 * This function iterates through all scene objects and computes the
 * distance to each one using their respective distance functions:
 * - **Sphere** → Calls `sphere_distance()`
 * - **Plane** → Calls `plane_distance()`
 *
 * The function **tracks the smallest positive distance**, updating:
 * - `ray->color` to store the color of the closest object.
 * - `closest_dist` to store the distance to the nearest intersection.
 *
 * If no intersection is found, the ray remains unchanged.
 *
 * Return:
 * - The distance to the **closest** intersecting object.
 * - If no object is found, returns `RENDER_DISTANCE` (a large max distance).
 */
double  closest(t_ray *ray, t_object *objects)
{
	double	dist;
	double	closest_dist;

	closest_dist = RENDER_DISTANCE;
	while (objects)
	{
		if (objects->type == SPHERE)
			dist = sphere_distance(ray->location, objects);
		else if (objects->type == PLANE)
			dist = plane_distance(ray->location, objects);
		else
			dist = closest_dist + 1;
		if (dist < closest_dist)
		{
			ray->color = objects->color;
			closest_dist = dist;
		}
		objects = objects->next;
	}
	return (closest_dist);
}
