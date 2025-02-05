#include "../includes/minirt.h"

t_objarr	*init_objarr(size_t capacity)
{
	t_objarr	*objarr;
	t_object	**arr;

	objarr = malloc(sizeof(t_objarr));
	arr = malloc(capacity * sizeof(t_object *));
	if (objarr == NULL || arr == NULL)
	{
		free(objarr);
		return (NULL);
	}
	ft_memset(arr, 0, capacity * sizeof(t_object *));
	objarr->arr = arr;
	objarr->capacity = capacity;
	objarr->objects = 0;
	return (objarr);
}

static int	reallocate(t_objarr *objarr)
{
	t_object **new;
	size_t i;

	objarr->capacity *= 2;
	new = malloc(objarr->capacity * sizeof(t_object *));
	if (new == NULL)
		return (FAILURE);
	ft_memset(new, 0, objarr->capacity * sizeof(t_object *));
	i = 0;
	while (objarr->arr[i] != NULL)
	{
		new[i] = objarr->arr[i];
		i++;
	}
	objarr->arr = new;
	return (SUCCESS);
}

int add(t_objarr *objarr, t_object *to_add)
{
	if (objarr == NULL)
	{
		printf("I did this\n");
		return (FAILURE);
	}
	if (objarr->capacity == objarr->objects + 1) // no more space after summing NULL terminator
		if (reallocate(objarr) == FAILURE)
			return (FAILURE);
	objarr->arr[objarr->objects] = to_add;
	objarr->objects++;
	return (SUCCESS);
}

void	free_objarr(t_objarr *objarr)
{
	size_t	i;

	i = 0;
	if (objarr && objarr->arr)
	{
		while (objarr->arr[i] != NULL)
		{
			free(objarr->arr[i]);
			i++;
		}
		free(objarr->arr);
	}
	free(objarr);
}
