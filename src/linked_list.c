#include "../inc/linked_list.h"

t_node	*last_node(t_node *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	add_node(t_node **list, t_node *new)
{
	t_node	*last;

	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	last = last_node(*list);
	last->next = new;
}

void	free_list(t_node *list)
{
	if (list == NULL)
		return ;
	free_list(list->next);
	free(list->data);
	free(list);
}

t_node	*create_node(void *data)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->data = data;
	node->next = NULL;
	return (node);
}
