#include "../includes/minirt.h"

/**
 * create_sphere - Initializes a sphere object.
 * @object: Pointer to the t_object to be initialized.
 * @info: Array of strings containing sphere parameters.
 *
 * This function:
 * - Sets the object type to `SPHERE`.
 * - Parses the **diameter** (`info[2]`).
 * - Parses the **color** (`info[3]`).
 * - Parses the **location** (`info[1]`).
 * - Validates the **diameter** (must be non-negative).
 * - If any parsing step fails, frees the object.
 *
 * Return:
 * - The function modifies the `object` in place.
 * - If invalid, the function frees the `object` and returns.
 */
void	create_sphere(t_object *object, char **info)
{
	object->type = SPHERE;
	object->diameter = parse_double(info[2]);
	object->color = parse_color(info[3]);
	if (parse_location(info[1], &(object->location)) < 0
		|| errno == EINVAL
		|| object->diameter < 0)
	{
		free(object);
		return ;
	}
	return ;
}

/**
 * create_plane - Initializes a plane object.
 * @object: Pointer to the t_object to be initialized.
 * @info: Array of strings containing plane parameters.
 *
 * This function:
 * - Sets the object type to `PLANE`.
 * - Parses the **color** (`info[3]`).
 * - Parses the **location** (`info[1]`).
 * - Parses the **orientation** (`info[2]`).
 * - Computes and stores **plane equation `d`** using the dot product.
 * - If any parsing step fails, frees the object.
 *
 * Return:
 * - The function modifies the `object` in place.
 * - If invalid, the function frees the `object` and returns.
 */
void	create_plane(t_object *object, char **info)
{
	object->type = PLANE;
	object->color = parse_color(info[3]);
	if (parse_location(info[1], &(object->location)) < 0
		|| parse_orientation(info[2], &(object->orientation)) < 0
		|| errno == EINVAL)
	{
		free(object);
		return ;
	}
	object->d = dot_product(object->orientation, object->location); // precalculation
	return ;
}

/**
 * create_cylinder - Initializes a cylinder object.
 * @object: Pointer to the t_object to be initialized.
 * @info: Array of strings containing cylinder parameters.
 *
 * This function:
 * - Sets the object type to `CYLINDER`.
 * - Parses the **diameter** (`info[3]`).
 * - Parses the **height** (`info[4]`).
 * - Parses the **color** (`info[5]`).
 * - Parses the **location** (`info[1]`).
 * - Parses the **orientation** (`info[2]`).
 * - Validates **diameter** and **height** (must be non-negative).
 * - If any parsing step fails, frees the object.
 *
 * Return:
 * - The function modifies the `object` in place.
 * - If invalid, the function frees the `object` and returns.
 */
void	create_cylinder(t_object *object, char **info)
{
	object->type = CYLINDER;
	object->diameter = parse_double(info[3]);
	object->height = parse_double(info[4]);
	object->color = parse_color(info[5]);
	if (parse_location(info[1], &(object->location)) < 0
		|| parse_orientation(info[2], &(object->orientation)) < 0
		|| object->diameter < 0
		|| object->height < 0
		|| errno == EINVAL)
	{
		free(object);
		return ;
	}
	return ;
}
