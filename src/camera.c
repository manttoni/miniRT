#include "../inc/object.h"

void	turn_camera(t_vector orientation

t_object	*get_camera(t_node *list)
{
	while (list)
	{
		if (list->data->type == CAMERA)
			return (list);
		list = list->next;
	}
	return (NULL);
}
