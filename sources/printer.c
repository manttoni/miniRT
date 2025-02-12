#include "../includes/minirt.h"

void camera_light_ambient(t_data *data)
{
	if (data->camera->type == CAMERA)
	{
		printf("Camera: 📷\n");
		printf("Orientation: ");
		print_vector(data->camera->orientation);
	}
	printf("---------------\n");
	if (data->light->light->type == LIGHT)
	{
		printf("Light: 💡\n");
		printf("Location: ");
		print_vector(data->light->light->location);
		printf("Brightness: %f\n", data->light->light->brightness);
	}
	printf("---------------\n");
	if (data->light->ambient->type == AMBIENT)
	{
		printf("Ambient light: 🌓\n");
		printf("Brightness: %f\n", data->light->ambient->brightness);
		printf("Color: \033[38;2;%d;%d;%dm%06X\033[0m\n",
			   (data->light->ambient->color >> 24) & 0xFF, (data->light->ambient->color >> 16) & 0xFF,
			   (data->light->ambient->color >> 8) & 0xFF, data->light->ambient->color);
	}
}

void the_objects(t_object *o)
{
	if (o->type == SPHERE)
		printf("Sphere: ⚪\n");
	else if (o->type == PLANE)
		printf("Plane: ✈️\n");
	else if (o->type == CYLINDER)
		printf("Cylinder: 🛢\n");
	printf("Location: ");
	print_vector(o->location);
	if (o->type == PLANE || o->type == CYLINDER)
	{
		printf("Orientation: ");
		print_vector(o->orientation);
	}
	if (o->type == SPHERE || o->type == CYLINDER)
		printf("Diameter: %f\n", o->diameter);
	printf("Color: \033[38;2;%d;%d;%dm%06X\033[0m\n",
		(o->color >> 24) & 0xFF, (o->color >> 16) & 0xFF,
		(o->color >> 8) & 0xFF, o->color);
}

void	print_object(t_object *o)
{
	if (o->type >= NONE)
	{
		printf("Unknown object\n");
		return ;
	}
	printf("---------------\n");
	if (o->type == SPHERE || o->type == PLANE || o->type == CYLINDER)
		the_objects(o);
}

void print_objects(t_data *data)
{
	size_t	i;

	i = 0;
	camera_light_ambient(data);
	while (i < data->objects->objects)
	{
		print_object(&data->objects->arr[i]);
		printf("Index: %zu\n", i);
		i++;
	}
	printf("---------------\n");
}
