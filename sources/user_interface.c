#include "../includes/minirt.h"

void    select_object(t_object *object, t_ui *ui)
{
    if (object == NULL)
    {
        printf("Object is NULL\n");
        return ;
    }
    if (ui == NULL)
    {
        printf("UI is NULL\n");
        return ;
    }
    ui->selected = object;
    printf("Object selected: \n");
    print_object(*object);
}