#include "../includes/minirt.h"
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
		printf("no node to add\n");
		free_list(*list);
		return (-1);
	}
	if (*list == NULL)
	{
		*list = new;
		return (1);
	}
	last = last_node(*list);
	last->next = new;
	return (1);
}

t_node	*create_node(void *data)
{
	t_node	*node;

	if (data == NULL)
	{
		printf("no data\n");
		return (NULL);
	}
	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->data = data;
	node->next = NULL;
	return (node);
}
