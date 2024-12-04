#include "../inc/object.h"

t_object	*create_ambient(char **info)
{
	t_object	*ambient;

	ambient = ft_calloc(1, sizeof(t_object));
	if (ambient == NULL)
		return (NULL);
	ambient->type = AMBIENT_LIGHT;
	ambient->brightness = parse_brightness(info[1]);
	ambient->color = parse_color(info[2]);
	// insert error handling here
	return (ambient);
}

t_object	*create_camera(char **info)
{
	t_object	*camera;

	camera = ft_calloc(1, sizeof(t_object));
	if (camera == NULL)
		return (NULL);
	camera->type = CAMERA;
	camera->location = parse_location(info[1]);
	camera->orientation = parse_orientation(info[2]);
	camera->fov = parse_fov(info[3]);
	// insert error handling here
	return (camera);
}

t_object	*create_light(char **info)
{
	t_object	*light;

	light = ft_calloc(1, sizeof(t_object));
	if (light == NULL)
		return (NULL);
	light->type = LIGHT;
	light->location = parse_location(info[1]);
	light->brightness = parse_brightness(info[2]);
	// insert error handling here
	return (light);
}
