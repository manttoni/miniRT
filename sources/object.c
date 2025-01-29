#include "../includes/minirt.h"

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
	else if (o->type == AMBIENT)
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

int	parse_object(t_object	*object, char *line)
{
	char		**info;

	printf("parse objects line: %s\n", line);
	info = ft_split(line, ' ');
	if (info == NULL)
		return 1;
	if (ft_strcmp(info[0], "A") == 0)
		create_ambient(object, info);
	else if (ft_strcmp(info[0], "C") == 0)
		create_camera(object, info);
	else if (ft_strcmp(info[0], "L") == 0)
		create_light(object, info);
	else if (ft_strcmp(info[0], "sp") == 0)
		create_sphere(object, info);
	else if (ft_strcmp(info[0], "pl") == 0)
		create_plane(object, info);
	else if (ft_strcmp(info[0], "cy") == 0)
		create_cylinder(object, info);
	ft_free_array(info);
	// printf("line: {%s} created object: {%p}\n", line, object);
	return 0;
}
