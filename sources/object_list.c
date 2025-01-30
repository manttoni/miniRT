#include "../includes/minirt.h"

/**
 * print_list - Prints all objects in a linked list.
 * @list: Pointer to the head of the object list.
 *
 * This function:
 * - Checks if the list is empty and prints `"List is empty"`.
 * - Iterates through the list, calling `print_object(list)` on each object.
 */
void	print_list(t_object *list)
{
	if (list == NULL)
	{
		printf("List is empty\n");
		return ;
	}
	while (list)
	{
		print_object(list);
		list = list->next;
	}
}

/**
 * last_object - Finds the last object in the linked list.
 * @list: Pointer to the head of the object list.
 *
 * This function:
 * - Returns `NULL` if the list is empty.
 * - Iterates through the list until it finds the **last object**.
 * - Returns a pointer to the last object.
 *
 * Return:
 * - Pointer to the last object in the list.
 * - NULL if the list is empty.
 */
t_object	*last_object(t_object *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/**
 * free_list - Recursively frees all objects in the list.
 * @list: Pointer to the head of the object list.
 *
 * This function:
 * - Recursively frees all objects by calling `free_list(list->next)`.
 * - Frees the current object.
 */
void	free_list(t_object *list)
{
	if (list == NULL)
		return ;
	free_list(list->next);
	free(list);
}

/**
 * add_node - Adds a new object to the linked list.
 * @list: Pointer to the head of the object list.
 * @new: Pointer to the new object to be added.
 *
 * This function:
 * - If `new` is NULL, frees the entire list and returns an error.
 * - If the list is empty, sets `new` as the first object.
 * - Otherwise, finds the last object using `last_object()` and adds `new` at the end.
 *
 * Return:
 * - 0 on success.
 * - 1 if `new` is NULL (error case).
 */
int	add_node(t_object **list, t_object *new)
{
	t_object	*last;

	if (new == NULL)
	{
		free_list(*list);
		return (1);
	}
	if (*list == NULL)
	{
		*list = new;
		return (0);
	}
	last = last_object(*list);
	last->next = new;
	return (0);
}

/**
 * create_node - Creates a new object node from a scene file line.
 * @line: The line containing object data.
 *
 * This function:
 * - Allocates memory for a new `t_object`.
 * - Calls `validate(line)` to check if the line format is correct.
 * - Calls `parse_object(node, validate(line))` to initialize object data.
 * - If validation or parsing fails, returns `NULL`.
 *
 * Return:
 * - Pointer to the newly created object.
 * - NULL if allocation or parsing fails.
 */
t_object	*create_node(char *line)
{
	t_object	*node;

	node = ft_calloc(1, sizeof(t_object));
	if (node == NULL)
		return (NULL);
	if (parse_object(node, validate(line)) == 1)
		return (NULL);
	return (node);
}
