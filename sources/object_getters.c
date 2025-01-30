#include "../includes/minirt.h"

/**
 * get_object - Finds and returns the first object of a specified type.
 * @objects: Pointer to the head of the linked list of objects.
 * @type: The type of object to search for.
 *
 * This function:
 * - Iterates through the linked list of objects.
 * - Checks if the current object's `type` matches the given `type`.
 * - If a match is found, returns a pointer to the object.
 * - If no object of the given type is found, returns `NULL`.
 *
 * Example Usage:
 * ```c
 * t_object *camera = get_object(scene_objects, CAMERA);
 * if (camera)
 *     printf("Camera found at location: (%f, %f, %f)\n",
 *            camera->location.x, camera->location.y, camera->location.z);
 * ```
 *
 * Return:
 * - A pointer to the first matching object found.
 * - NULL if no object of the specified type exists.
 */
t_object	*get_object(t_object *objects, t_type type)
{
	while (objects)
	{
		if (objects->type == type)
			return (objects);
		objects = objects->next;
	}
	return (NULL);
}
