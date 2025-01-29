#include "../includes/object.h"

t_object	*get_object(t_object *objects, t_type type)
{
	while (objects)
	{
		if (objects->type == type)
			return (objects);
		objects = objects->next;
	}
	return (NULL);
}
