#include "../includes/minirt.h"

void print_objects(t_object *objects)
{
	t_object *o;

	o = objects;
	while (o)
	{
		print_object(o);
		o = o->next;
	}
	printf("---------------\n");
}

/**
 * format_validation - Checks if the provided file has the correct ".rt" extension.
 * @str: The filename as a string.
 *
 * This function validates the file format by checking if the last three
 * characters of the string match ".rt". If they do not, it returns 1
 * (indicating an invalid format), otherwise, it returns 0 (valid format).
 *
 * Return: 1 if the file format is incorrect, 0 if valid.
 */
static int	format_validation(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strncmp(&str[len - 3], ".rt", 3) != 0)
		return (1);
	return (0);
}

/**
 * main - Entry point for the miniRT program.
 * @argc: Number of command-line arguments.
 * @argv: Array of arguments (expects a filename with ".rt").
 *
 * This function handles:
 * 1. Checking if the correct number of arguments is provided.
 * 2. Validating that the provided file has the correct ".rt" extension.
 * 3. Initializing the data structure (parses objects from the file).
 * 4. Running the ray tracing rendering process.
 * 5. Handling user interactions via keyboard hooks.
 * 6. Displaying the final rendered image in an MLX42 window.
 * 7. Cleaning up allocated memory before exiting.
 *
 * Return: 0 on successful execution, 1 on failure.
 */
int main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
	{
		printf("Wrong amount of arguments!\n");
		return (1);
	}
	if (format_validation(argv[1]))
	{
		printf("Wrong type of file\n");
		return (1);
	}
	data = init_data(argv[1]);
	if (data == NULL)
		return (1);
	print_objects(data->objects);
	raycast(data);
	mlx_key_hook(data->mlx, &keypress, data);
	mlx_image_to_window(data->mlx, data->image , 0, 0);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	free_data(data);
	return (0);
}
