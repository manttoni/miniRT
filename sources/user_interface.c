#include "../includes/minirt.h"

void    select_object(t_object *object, t_ui *ui)
{
    ui->selected = object;
    printf("Object selected: \n");
    print_object(*object);
}