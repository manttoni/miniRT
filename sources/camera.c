#include "../inc/object.h"

t_object	*get_camera(t_node *objects)
{
	t_object	*object;

	while (objects)
	{
		object = (t_object *) objects->data;
		if (object->type == CAMERA)
			return (object);
		objects = objects->next;
	}
	return (NULL);
}