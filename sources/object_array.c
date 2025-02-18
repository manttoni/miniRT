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
	t_object	*new_arr;
	size_t		i;

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
int	add_cla(t_data *data, char *line)
{
	if (line[0] == 'C' && data->camera->type == NONE)
		return (parse_object(data->camera, line));
	if (line[0] == 'L' && data->light->light->type == NONE)
		return (parse_object(data->light->light, line));
	if (line[0] == 'A' && data->ambient->ambient->type == NONE)
		return (parse_object(data->ambient->ambient, line));
	return (failure("Duplicate camera, light or ambient"));
}

/*	Adds an object to the array
	parse_object parses that object from line
	if array is full, doubles the arrays allocated memory 
	CLA are instead put in data */
int	add_object(t_data *data, char *line)
{
	t_object	*object;

	if (validate(line) == FAILURE)
		return (failure("Validation failed"));
	if (ft_strchr("CLA", line[0]) != NULL)
		return (add_cla(data, line));
	if (data->objects->capacity == data->objects->objects)
		if (reallocate(data->objects) == FAILURE)
			return (failure("Malloc failed"));
	object = data->objects->arr + data->objects->objects;
	if (parse_object(object, line) == FAILURE)
		return (failure("parse_object failed"));
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
