
#include "../includes/minirt.h"

/**
 * create_ambient - Initializes an ambient light object.
 * @object: Pointer to the t_object to be initialized.
 * @info: Array of strings containing ambient light parameters.
 *
 * This function:
 * - Sets the object type to `AMBIENT`.
 * - Parses brightness (`info[1]`) and RGB color (`info[2]`).
 * - Validates brightness (should be between 0 and 1).
 * - If invalid, frees the object.
 */
void	create_ambient(t_object *object, char **info)
{
	object->type = AMBIENT;
	object->brightness = parse_double(info[1]);
	object->color = parse_color(info[2]);
	if (object->brightness < 0 || object->brightness > 1)
	{
		free(object);
		return ;
	}
	return ;
}

/**
 * image_plane - Computes the camera's image plane and primary ray.
 * @camera: Pointer to the camera object.
 *
 * This function:
 * - Computes the **right vector (`u`)** perpendicular to the camera's orientation.
 * - Computes the **up vector (`v`)** using the cross-product.
 * - Computes the **primary ray direction** based on the camera's location and orientation.
 * - Sets the initial ray color to `BACKGROUND_COLOR`.
 *
 * Return:
 * - A `t_camera_info` struct containing the computed vectors and primary ray.
 */
t_camera_info	image_plane(t_object *camera)
{
	t_camera_info	info;

	if (camera->orientation.x == 0 && camera->orientation.y == 0)
		info.u = vector(1, 0, 0);
	else if (camera->orientation.y == 0 && camera->orientation.z == 0)
		info.u = vector (0, 1, 0);
	else if (camera->orientation.z == 0 && camera->orientation.x == 0)
		info.u = vector (0, 0, 1);
	else
		info.u = vector(-camera->orientation.y, camera->orientation.x, 0);
	info.v = cross_product(camera->orientation, info.u);
	info.ray.location = camera->location;
	info.ray.direction = v_mul(camera->info.view_distance, camera->orientation);
	info.ray.direction = v_sum(camera->location, info.ray.direction);
	info.ray.distance = 0;
	info.ray.color = BACKGROUND_COLOR;
	return (info);
}

/**
 * create_camera - Initializes a camera object.
 * @object: Pointer to the t_object to be initialized.
 * @info: Array of strings containing camera parameters.
 *
 * This function:
 * - Sets the object type to `CAMERA`.
 * - Parses the **field of view (FOV)**.
 * - Parses **location and orientation**.
 * - Validates FOV (should be between 0 and 180).
 * - Computes the camera's **image plane vectors**.
 * - Sets a default **view distance** of 600.
 * - If invalid, frees the object.
 */
void	create_camera(t_object *object, char **info)
{
	object->type = CAMERA;
	object->fov = ft_atoi(info[3]);
	parse_location(info[1], &(object->location));
	parse_orientation(info[2], &(object->orientation));
	if (object->fov < 0 || object->fov > 180)
	{
		free(object);
		return ;
	}
	object->info.view_distance = 600;
	object->info = image_plane(object);
	return ;
}

/**
 * create_light - Initializes a light object.
 * @object: Pointer to the t_object to be initialized.
 * @info: Array of strings containing light parameters.
 *
 * This function:
 * - Sets the object type to `LIGHT`.
 * - Parses brightness (`info[2]`).
 * - Parses RGB color (`info[3]`).
 * - Parses location (`info[1]`).
 * - Validates brightness (should be between 0 and 1).
 * - If invalid, frees the object.
 */
void	create_light(t_object *object, char **info)
{
	object->type = LIGHT;
	object->brightness = parse_double(info[2]);
	object->color = parse_color(info[3]);
	parse_location(info[1], &(object->location));
	if (object->brightness < 0 || object->brightness > 1)
	{
		free(object);
		return ;
	}
	return ;
}

