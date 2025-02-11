#include "../includes/minirt.h"

/* data->ui holds the selected object which reacts to movement keys */
void    select_object(t_object *object, t_object *selected)
{
    selected = object;
    printf("Object selected: \n");
    print_object(object);
}
