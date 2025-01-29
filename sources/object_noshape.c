
#include "../includes/minirt.h"

void	create_ambient(t_object *object, char **info)
{
	object->type = AMBIENT;
	object->brightness = parse_double(info[1]);
	object->color = parse_color(info[2]);
	if (object->brightness < -1 || object->brightness > 1 || errno == EINVAL)
	{
		free(object);
		return ;
	}
	return ;
}

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

void	create_camera(t_object *object, char **info)
{
	object->type = CAMERA;
	object->fov = ft_atoi(info[3]);
	if (parse_location(info[1], &(object->location)) < 0
		|| parse_orientation(info[2], &(object->orientation)) < 0
		|| object->fov < 0 || object->fov > 180)
	{
		free(object);
		return ;
	}
	object->info.view_distance = 600;
	object->info = image_plane(object);
	return ;
}

void	create_light(t_object *object, char **info)
{
	object->type = LIGHT;
	object->brightness = parse_double(info[2]);
	if (parse_location(info[1], &(object->location)) < 0
		|| object->brightness < -1 || object->brightness > 1)
	{
		printf("light creation failed\n");
		printf("--------\ninfo about light\n");
		printf("brightness: %f\n", object->brightness);
		print_vector(object->location);
		printf("errno: %d\n", errno);
		printf("----------\n");
		free(object);
		return ;
	}
	return ;
}

