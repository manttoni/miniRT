
#include "../includes/minirt.h"

/**
 * add_to_list - Creates a new object and adds it to the linked list.
 * @list: Pointer to the head of the object list.
 * @info: The object data string from the scene file.
 *
 * This function:
 * - Calls `create_node(info)` to allocate and initialize a new object.
 * - Calls `add_node(list, object)` to insert the new object into the linked list.
 * - If `create_node` or `add_node` fails, it **frees the entire list** to prevent memory leaks.
 *
 * Return:
 * - 0 on success.
 * - 1 on failure (if memory allocation or list insertion fails).
 */
int	add_to_list(t_object **list, char *info)
{

	t_object *object;

	object = create_node(info);
	if (object == NULL || add_node(list, object))
	{
		free_list(*list);
		*list = NULL;
		return (1);
	}
	return (0);
}

/**
 * read_objects - Reads and parses objects from a scene file.
 * @file: The filename containing the scene description.
 *
 * This function:
 * - Opens the file and reads line by line using `get_next_line(fd)`.
 * - Trims newline characters from each line using `trim(line, '\n')`.
 * - Ignores commented lines (`#` at the start).
 * - Calls `add_to_list(&list, line)` to create and store each object.
 * - Closes the file and returns the linked list of objects.
 *
 * If the file cannot be opened or parsing fails, it prints an error message.
 *
 * Return:
 * - Pointer to the head of the object list on success.
 * - NULL on failure.
 */
t_object	*read_objects(char	*file)
{
	char		*line;
	int			fd;
	t_object		*list;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("failed to open file\n");
		return (NULL);
	}
	list = NULL;
	line = get_next_line(fd);
	while (line)
	{
		line = trim(line, '\n');
		if (*line != '#' && add_to_list(&list, line))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (list);
}
