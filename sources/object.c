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
	printf("---------------\n");
}

t_type  get_type(char *line)
{
    char    *shapes[7];
    int     i;

    shapes[CAMERA] = "C ";
    shapes[LIGHT] = "L ";
    shapes[AMBIENT] = "A ";
    shapes[SPHERE] = "sp ";
    shapes[PLANE] = "pl ";
    shapes[CYLINDER] = "cy ";
    shapes[NONE] = NULL;
    i = 0;
    while (shapes[i] != NULL)
    {
        if (ft_strncmp(shapes[i], line, ft_strlen(shapes[i])) == 0)
            return (i);
        i++;
    }
    return (NONE);
}

int	parse_object(t_object	*object, char *line)
{
	char		**info;

	info = ft_split(line, ' ');
	if (info == NULL)
		return 1;
	if (get_type(line) == AMBIENT)
		create_ambient(object, info);
	else if (get_type(line) == CAMERA)
		create_camera(object, info);
	else if (get_type(line) == LIGHT)
		create_light(object, info);
	else if (get_type(line) == SPHERE)
		create_sphere(object, info);
	else if (get_type(line) == PLANE)
		create_plane(object, info);
	else if (get_type(line) == CYLINDER)
		create_cylinder(object, info);
	ft_free_array(info);
	return 0;
}
