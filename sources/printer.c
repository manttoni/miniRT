#include "../includes/minirt.h"

void	camera_light_ambient(t_object *c, t_object *l, t_object *a)
{
	printf("---------------\n");
	if (c)
	{
		printf("Camera: 📷\n");
		printf("Orientation: ");
		print_vector(c->orientation);
		printf("---------------\n");
	}
	if (l)
	{
		printf("Light: 💡\n");
		printf("Location: ");
		print_vector(l->location);
		printf("Brightness: %f\n", l->brightness);
		printf("---------------\n");
	}
	if (a)
	{
		printf("Ambient light: 🌓\n");
		printf("Brightness: %f\n", a->brightness);
		printf("Color: \033[38;2;%d;%d;%dm%06X\033[0m\n",
			(a->color >> 24) & 0xFF, (a->color >> 16) & 0xFF,
			(a->color >> 8) & 0xFF, a->color);
		printf("---------------\n");
	}
}

void	the_objects(t_object *o)
{
	printf("---------------\n");
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
	printf("---------------\n");
}

void	print_vector(t_vector v)
{
	printf("x: %1.2f, y: %1.2f, z: %1.2f, len: %1.2f\n",
		v.x, v.y, v.z, v_len(v));
}

void	print_objects(t_data *data)
{
	size_t	i;

	i = 0;
	camera_light_ambient(data->camera, data->light->light,
		data->ambient->ambient);
	while (i < data->objects->objects)
	{
		the_objects(&data->objects->arr[i]);
		printf("Index: %zu\n", i);
		i++;
	}
}

void	print_help(void)
{
	printf("--------------\n");
	printf("HOME: print objects\n");
	printf("COMMA: this menu\n");
	printf("Select object: right click, number keys and C L A\n");
	printf("Movement keys (numpad):\n");
	printf("L/R: 4 & 6\nUP/DOWN: 8 & 2\nFORWARD/BACK: 9 & 1\n");
	printf("Left click rotates camera\n");
	printf("Arrow keys rotate selected object\n");
	printf("Numpad + and - change brightness, fov or diameter\n");
	printf("Page up and down change cylinder height\n");
}