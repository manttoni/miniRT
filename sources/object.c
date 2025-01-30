#include "../includes/minirt.h"

/**
 * print_object - Prints details of a scene object.
 * @o: Pointer to the `t_object` structure.
 *
 * This function:
 * - Displays the **type of the object** using emojis.
 * - Prints the **location** if applicable.
 * - Prints the **orientation** for applicable objects.
 * - Displays **FOV** for cameras.
 * - Displays **diameter** for spheres and cylinders.
 * - Prints the **color** in RGB format with ANSI escape codes.
 */
void print_object(t_object *o)
{
	if (o == NULL)
	{
		printf("Object not found!\n");
		return ;
	}
	printf("---------------\n");
	if (o->type == CAMERA)
		printf("Camera: 📷\n");
	else if (o->type == SPHERE)
		printf("Sphere: ⚪\n");
	else if (o->type == PLANE)
		printf("Plane: ✈️\n");
	else if (o->type == AMBIENT)
		printf("Ambient light: 💡\n");
	else if (o->type == LIGHT)
		printf("Light: 💡\n");
	else if (o->type == CYLINDER)
		printf("Cylinder: 🛢\n");
	if (o->type != AMBIENT)
	{
		printf("Location: ");
		print_vector(o->location);
	}
	if (o->type == CAMERA || o->type == PLANE || o->type == CYLINDER)
	{
		printf("Orientation: ");
		print_vector(o->orientation);
	}
	if (o->type == CAMERA)
		printf("FOV: %d\n", o->fov);
	if (o->type == SPHERE || o->type == CYLINDER)
		printf("Diameter: %f\n", o->diameter);
	if (o->type != CAMERA && o->type != LIGHT)
	{
		printf("Color: \033[38;2;%d;%d;%dm%06X\033[0m\n",
           (o->color >> 16) & 0xFF, (o->color >> 8) & 0xFF,
           o->color & 0xFF, o->color);
	}
}

/**
 * get_type - Determines the type of object from a scene line.
 * @line: The input line from the scene file.
 *
 * This function:
 * - Compares the first word of the line with predefined object identifiers.
 * - Uses a lookup array to check object types efficiently.
 *
 * Return:
 * - The corresponding `t_type` value (`CAMERA`, `SPHERE`, `PLANE`, etc.).
 * - `NONE` if no valid type is found.
 */
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

/**
 * parse_object - Parses a scene object from a line.
 * @object: Pointer to the `t_object` to be initialized.
 * @line: The input line from the scene file.
 *
 * This function:
 * - Splits the line into an array of words.
 * - Determines the object type using `get_type()`.
 * - Calls the corresponding creation function (`create_sphere`, `create_plane`, etc.).
 * - Frees the allocated array after parsing.
 *
 * Return:
 * - `0` on success.
 * - `1` if parsing fails.
 */
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
