#include "../includes/minirt.h"

/* data->ui holds the selected object which reacts to movement keys */
void	select_object(t_object *object, t_data *data)
{
	data->selected = object;
	printf("Object selected: \n");
	the_objects(object);
}
