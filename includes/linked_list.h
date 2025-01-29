#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include <stdlib.h>
# include "../libft/includes/libft.h"
# include "object.h"

typedef struct	s_node
{
	void			*data;
	struct s_node	*next;
}	t_node;

t_node	*last_node(t_node *list);
int		add_node(t_node **list, t_node *new);
void	free_list(t_node *list);
t_object	*create_node(char *line);

#endif
