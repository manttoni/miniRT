#include "../includes/minirt.h"

/* Returns a pointer to the first object that has the matching type*/
t_object	*get_object(t_objarr *objarr, t_type type)
{
	size_t	i;

	i = 0;
	while (i < objarr->objects)
	{
		if (objarr->arr[i].type == type)
			return (&(objarr->arr[i]));
		i++;
	}
	return (NULL);
}
