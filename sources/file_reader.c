/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:41:24 by nzharkev          #+#    #+#             */
/*   Updated: 2025/02/18 16:16:31 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * error_check - Checks for file descriptor and object array validity.
 *
 * @fd: The file descriptor to check.
 * @objarr: Pointer to the object array structure.
 *
 * This function ensures that the file descriptor is valid (not negative)
 * and that the object array has been allocated. If either is invalid,
 * it closes the file descriptor (if open) and frees the object array.
 *
 * Return: SUCCESS (0) if no errors, otherwise FAILURE (-1).
 */
static int	error_check(int fd, t_objarr *objarr)
{
	if (objarr == NULL || fd < 0)
	{
		if (fd > 2)
			close(fd);
		free_objarr(objarr);
		return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * unique_check - Ensures required scene elements exist.
 *
 * @data: Pointer to the main program data structure.
 *
 * This function verifies that the scene has a camera, a light source,
 * ambient lighting, and at least one visible object. If any of these
 * elements are missing, an error message is printed.
 *
 * Return: SUCCESS (0) if all elements are present, otherwise FAILURE (-1).
 */
static int	unique_check(t_data *data)
{
	if (data->camera->type == NONE)
		return (failure("No camera"));
	if (data->light->obj->type == NONE)
		return (failure("No light"));
	if (data->ambient->obj->type == NONE)
		return (failure("No ambient"));
	if (data->objects->objects < 1)
		return (failure("No visible object"));
	return (SUCCESS);
}

int	in_read(t_data *data, char **line, int fd)
{
	if (**line != '\0' && **line != '#' && add_object(data, *line) == FAILURE)
	{
		free(*line);
		close(fd);
		return (FAILURE);
	}
	free(*line);
	*line = trim_newline(get_next_line(fd));
	return (SUCCESS);
}

/**
 * read_objects - Parses the scene description file and loads objects.
 *
 * @data: Pointer to the main program data structure.
 *
 * This function reads the scene description file specified in `data->file`.
 * It initializes an object array, checks for errors, and then reads the file
 * line by line. Each line is processed and added as an object to the scene.
 *
 * Lines starting with '#' are treated as comments and ignored.
 * If an error occurs while adding an object, the function terminates early.
 *
 * Once all objects are loaded, `set_precalculations` is called to prepare
 * data for rendering.
 *
 * Return: SUCCESS if the scene is successfully loaded, otherwise FAILURE.
 */
int	read_objects(t_data *data)
{
	char		*line;
	int			fd;
	t_objarr	*objarr;

	fd = open(data->file, O_RDONLY);
	objarr = init_objarr(4);
	if (error_check(fd, objarr) == FAILURE)
		return (FAILURE);
	data->objects = objarr;
	line = trim_newline(get_next_line(fd));
	while (line)
	{
		if (in_read(data, &line, fd) == FAILURE)
			return (FAILURE);
	}
	close(fd);
	if (unique_check(data) == SUCCESS)
	{
		set_precalculations(data);
		return (SUCCESS);
	}
	return (FAILURE);
}
