#include "../inc/object.h"

t_object	*create_ambient(char **info)
{
	t_object	*ambient;

	ambient = ft_calloc(1, sizeof(t_object));
	if (ambient == NULL)
		return (NULL);
	ambient->type = AMBIENT_LIGHT;
	ambient->brightness = parse_double(info[1]);
	ambient->color = parse_color(info[2]);
	if (ambient->brightness < -1 || ambient->brightness > 1 || errno == EINVAL)
	{
		free(ambient);
		return(NULL);
	}
	return (ambient);
}

t_object	*create_camera(char **info)
{
	t_object	*camera;

	camera = ft_calloc(1, sizeof(t_object));
	if (camera == NULL)
		return (NULL);
	camera->type = CAMERA;
	camera->fov = ft_atoi(info[3]);
	if (parse_location(info[1], &(camera->location)) < 0
		|| parse_orientation(info[2], &(camera->orientation)) < 0
		|| camera->fov < 0 || camera->fov > 180)
	{
		free(camera);
		return (NULL);
	}
	return (camera);
}

t_object	*create_light(char **info)
{
	t_object	*light;

	light = ft_calloc(1, sizeof(t_object));
	if (light == NULL)
		return (NULL);
	light->type = LIGHT;
	light->brightness = parse_double(info[2]);
	if (parse_location(info[1], &(light->location)) < 0
		|| light->brightness < -1 || light->brightness > 1)
	{
		printf("light creation failed\n");
		printf("--------\ninfo about light\n");
		printf("brightness: %f\n", light->brightness);
		print_vector(light->location);
		printf("errno: %d\n", errno);
		printf("----------\n");
		free(light);
		return (NULL);
	}
	return (light);
}
