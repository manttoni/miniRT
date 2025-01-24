#include "../includes/minirt.h"

t_object	*get_object(t_node *objects, t_type type)
{
	t_object	*object;

	while (objects)
	{
		object = (t_object *) objects->data;
		if (object->type == type)
			return (object);
		objects = objects->next;
	}
	return (NULL);
}