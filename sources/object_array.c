/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:03:37 by nzharkev          #+#    #+#             */
/*   Updated: 2025/02/18 15:32:48 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * add_cla - Adds a Camera, Light, or Ambient object to the scene.
 *
 * @data: Pointer to the scene data.
 * @line: Input line containing object data.
 *
 * This function ensures that there is only one instance of each of these
 * elements in the scene. If a duplicate is found, it returns an error.
 *
 * Return: SUCCESS if the object is added successfully, otherwise FAILURE.
 */
static int	add_cla(t_data *data, char *line)
{
	if (line[0] == 'C' && data->camera->type == NONE)
		return (parse_object(data->camera, line));
	if (line[0] == 'L' && data->light->obj->type == NONE)
		return (parse_object(data->light->obj, line));
	if (line[0] == 'A' && data->ambient->obj->type == NONE)
		return (parse_object(data->ambient->obj, line));
	return (failure("Duplicate camera, light or ambient"));
}

/**
 * reallocate - Expands the capacity of the object array.
 *
 * @objarr: Pointer to the object array structure.
 *
 * This function doubles the array capacity and reallocates memory.
 * It preserves existing data while increasing available storage.
 *
 * Return: SUCCESS if reallocation succeeds, otherwise FAILURE.
 */
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

/**
 * init_objarr - Initializes an object array with a given capacity.
 *
 * @capacity: Initial number of objects that the array can hold.
 *
 * This function allocates memory for the object array and initializes
 * the object count to zero.
 *
 * Return: Pointer to the allocated object array, or NULL if allocation fails.
 */
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

/**
 * add_object - Adds an object to the scene.
 *
 * @data: Pointer to the scene data.
 * @line: Input line containing object data.
 *
 * This function validates the input, checks if the object is a Camera,
 * Light, or Ambient, and ensures sufficient storage capacity.
 * If necessary, it reallocates the object array.
 *
 * Return: SUCCESS if the object is added, otherwise FAILURE.
 */
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

/**
 * free_objarr - Frees memory allocated for the object array.
 *
 * @objarr: Pointer to the object array structure.
 *
 * This function safely deallocates memory used by the object array,
 * ensuring no memory leaks occur.
 */
void	free_objarr(t_objarr *objarr)
{
	if (objarr == NULL)
		return ;
	free(objarr->arr);
	free(objarr);
}
