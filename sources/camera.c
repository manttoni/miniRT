#include "../includes/minirt.h"

int assign_camera(t_object *camera, char **info)
{
	camera->location = parse_vector(info[1]);
	camera->orientation = parse_vector(info[2]);
	camera->fov = ft_atoi(info[3]);
	camera->orientation = normalize_vector(camera->orientation);
	if (camera->fov < 0 || camera->fov > 180)
		return (failure("FOV not valid"));
	//camera->info = image_plane(camera);
	return (SUCCESS);
}