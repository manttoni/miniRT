#include "../includes/object.h"

void print_object(t_object *o)
{
	if (o == NULL)
	{
		printf("Object not found!\n");
		return ;
	}
	if (o->type == CAMERA)
	{
		printf("---------------\n");
		printf("Camera: 📷\nLocation: ");
		print_vector(o->location);
		printf("Orientation: ");
		print_vector(o->orientation);
		printf("FOV: %d\n", o->fov);
	}
	else if (o->type == SPHERE)
	{
		printf("---------------\n");
		printf("Sphere: ⚪\nLocation: ");
		print_vector(o->location);
		printf("Diameter: %f\n", o->diameter);
		printf("Color: %x\n", o->color);
	}
	else if (o->type == PLANE)
	{
		printf("---------------\n");
		printf("Plane: ✈️\nLocation: ");
		print_vector(o->location);
		printf("Normal: ");
		print_vector(o->orientation);
		printf("Color: %x\n", o->color);
	}
	else if (o->type == AMBIENT_LIGHT)
	{
		printf("---------------\n");
		printf("Ambient light: 💡\nLocation: ");
		print_vector(o->location);
		printf("Normal: ");
		print_vector(o->orientation);
		printf("Color: %x\n", o->color);
	}
	else if (o->type == LIGHT)
	{
		printf("---------------\n");
		printf("Light: 💡\nLocation: ");
		print_vector(o->location);
		printf("Normal: ");
		print_vector(o->orientation);
		printf("Color: %x\n", o->color);
	}
	else if (o->type == CYLINDER)
	{
		printf("---------------\n");
		printf("Cylinder: 🛢\nLocation: ");
		print_vector(o->location);
		printf("Normal: ");
		print_vector(o->orientation);
		printf("Color: %x\n", o->color);
	}
}

t_object	*parse_object(char *line)
{
	char		**info;
	t_object	*object;

	if (line == NULL)
	{
		printf("line is null\n");
		return (NULL);
	}
	object = NULL;
	info = ft_split(line, ' ');
	if (info == NULL)
		return (NULL);
	if (ft_strcmp(info[0], "A") == 0)
		object = create_ambient(info);
	else if (ft_strcmp(info[0], "C") == 0)
		object = create_camera(info);
	else if (ft_strcmp(info[0], "L") == 0)
		object = create_light(info);
	else if (ft_strcmp(info[0], "sp") == 0)
		object = create_sphere(info);
	else if (ft_strcmp(info[0], "pl") == 0)
		object = create_plane(info);
	else if (ft_strcmp(info[0], "cy") == 0)
		object = create_cylinder(info);
	else
		printf("Wrong identifier!\n");
	ft_free_array(info);
	// printf("line: {%s} created object: {%p}\n", line, object);
	return (object);
}
