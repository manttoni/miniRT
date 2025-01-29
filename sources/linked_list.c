#include "../includes/object.h"
#include <stdio.h>

t_node	*last_node(t_node *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	free_list(t_node *list)
{
	if (list == NULL)
		return ;
	free_list(list->next);
	free(list->data);
	free(list);
}

int	add_node(t_node **list, t_node *new)
{
	t_node	*last;

	if (new == NULL)
	{
		// printf("no node to add\n");
		free_list(*list);
		return (1);
	}
	if (*list == NULL)
	{
		*list = new;
		return (0);
	}
	last = last_node(*list);
	last->next = new;
	return (0);
}

t_object	*create_node(char *line)
{
	return (parse_object(validate(line)));
}