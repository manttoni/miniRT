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

/*	Adds an object to the array
	parse_object parses that object from line
	if array is full, doubles the arrays allocated memory */
int add_object(t_data *data, char *line)
{
	if (validate(line) == NULL)
		return (failure("Validation failed"));
	if (line[0] == 'C')
	{
		data->camera = assign_camera(data->camera, line);
		return (SUCCESS);
	}
    if (data->objects->capacity == data->objects->objects)
        if (reallocate(data->objects) == FAILURE)
			return (FAILURE);
    if (parse_object(data->objects->arr + data->objects->objects, line) == FAILURE)
		return (FAILURE);
	data->objects->objects++;
    return (SUCCESS);
}

void	free_objarr(t_objarr *objarr)
{
	if (objarr == NULL)
		return ;
	free(objarr->arr);
	free(objarr);
}
