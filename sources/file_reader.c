/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:41:24 by nzharkev          #+#    #+#             */
/*   Updated: 2025/02/18 13:41:28 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
		if (*line != '\0' && *line != '#' && add_object(data, line) == FAILURE)
		{
			free_objarr(objarr);
			free(line);
			close(fd);
			return (FAILURE);
		}
		free(line);
		line = trim_newline(get_next_line(fd));
	}
	close(fd);
	set_precalculations(data);
	return (SUCCESS);
}
