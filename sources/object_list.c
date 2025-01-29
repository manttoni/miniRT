#include "../includes/minirt.h"

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

t_object	*last_object(t_object *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	free_list(t_object *list)
{
	if (list == NULL)
		return ;
	free_list(list->next);
	free(list);
}

int	add_node(t_object **list, t_object *new)
{
	t_object	*last;

	if (new == NULL)
	{
		free_list(*list);
		return (1);
	}
	print_object(new);
	if (*list == NULL)
	{
		*list = new;
		return (0);
	}
	last = last_object(*list);
	last->next = new;
	return (0);
}

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
