#include "../includes/minirt.h"

char *str_vector(t_vector v)
{
	char	*print;

    print = malloc(100);
	ft_bzero(print, 100);
	snprintf(print, 100, "%f,%f,%f", v.x, v.y, v.z);
    return print;
}

char *str_color(uint32_t c)
{
	char	*print;

    print = malloc(100);
	ft_bzero(print, 100);
	snprintf(print, 100, "%d,%d,%d", (c >> 24) & 0xFF, (c >> 16) & 0xFF, (c >> 8) & 0xFF);
    return print;
}

void	save_scene(t_data *data)
{
	size_t		i;
	t_object	*o;

	o = data->camera;
	printf("C %s %s %d\n", str_vector(o->location), str_vector(o->orientation), o->fov);
	o = data->light->light;
	printf("L %s %f\n", str_vector(o->location), o->brightness);
	o = data->ambient->ambient;
	printf("A %f %s\n", o->brightness, str_color(o->color));
	i = 0;
	while (i < data->objects->objects)
	{
		o = &data->objects->arr[i];
		if (o->type == SPHERE)
			printf("sp %s %f %s\n", str_vector(o->location), o->diameter, str_color(o->color));
		else if (o->type == PLANE)
			printf("pl %s %s %s\n", str_vector(o->location), str_vector(o->orientation), str_color(o->color));
		else
			printf("cy %s %s %f %f %s\n", str_vector(o->location), str_vector(o->orientation), o->diameter, o->height, str_color(o->color));
		i++;
	}
}