#include "../includes/minirt.h"

t_object	*get_object(t_object **arr, t_type type)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i]->type == type)
			return (arr[i]);
		i++;
	}
	return (NULL);
}
