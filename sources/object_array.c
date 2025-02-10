#include "../includes/minirt.h"

t_objarr	*init_objarr(size_t capacity)
{
	t_objarr	*objarr;
	t_object	*arr;

	objarr = malloc(sizeof(t_objarr));
	arr = malloc(capacity * sizeof(t_object));
	if (objarr == NULL || arr == NULL)
	{
		free(objarr);
		return (NULL);
	}
	ft_memset(arr, 0, capacity * sizeof(t_object));
	objarr->arr = arr;
	objarr->capacity = capacity;
	objarr->objects = 0;
	return (objarr);
}

static int	reallocate(t_objarr *objarr)
{
    t_object    *new_arr;
    size_t      i;

	objarr->capacity *= 2;
    new_arr = malloc(objarr->capacity * sizeof(t_object));
    if (new_arr == NULL)
		return (FAILURE);
	ft_memset(new_arr, 0, objarr->capacity * sizeof(t_object));
	i = 0;
    while (i < objarr->objects)
	{
		new_arr[i] = objarr->arr[i];
		i++;
	}
	free(objarr->arr);
	objarr->arr = new_arr;
	return (SUCCESS);
}

int add_object(t_objarr *objarr, char *line)
{
	if (objarr == NULL)
		return (FAILURE);
    if (objarr->capacity == objarr->objects)
        if (reallocate(objarr) == FAILURE)
			return (FAILURE);
    if (parse_object(objarr->arr + objarr->objects, line) == FAILURE)
		return (FAILURE);
	objarr->objects++;
    return (SUCCESS);
}

void	free_objarr(t_objarr *objarr)
{
	if (objarr->arr)
		free(objarr->arr);
	free(objarr);
}
