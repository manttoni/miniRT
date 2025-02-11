#include "../includes/minirt.h"

void camera_light_ambient(t_object *o)
{
	if (o->type == CAMERA)
		printf("Camera: 📷\n");
	else if (o->type == AMBIENT)
		printf("Ambient light: 🌓\n");
	else if (o->type == LIGHT)
		printf("Light: 💡\n");
	if (o->type != AMBIENT)
	{
		printf("Location: ");
		print_vector(o->location);
	}
	if (o->type == CAMERA)
	{
		// printf("FOV: %d\nView distance: %1.2f\n", o->fov, o->info.view_distance);
		printf("Orientation: ");
		print_vector(o->orientation);
	}
	if (o->type != CAMERA && o->type != LIGHT)
	{
		printf("Color: \033[38;2;%d;%d;%dm%06X\033[0m\n",
			   (o->color >> 24) & 0xFF, (o->color >> 16) & 0xFF,
			   (o->color >> 8) & 0xFF, o->color);
	}
	if (o->type == LIGHT || o->type == AMBIENT)
		printf("Brightness: %f\n", o->brightness);
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
	if (o->type == CAMERA || o->type == AMBIENT || o->type == LIGHT)
		camera_light_ambient(o);
	if (o->type == SPHERE || o->type == PLANE || o->type == CYLINDER)
		the_objects(o);
}

void print_objects(t_objarr *objarr)
{
	size_t	i;

	i = 0;
	while (i < objarr->objects)
	{
		print_object(&objarr->arr[i]);
		printf("Index: %zu\n", i);
		i++;
	}
	printf("---------------\n");
}
