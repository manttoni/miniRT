/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:50:26 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 11:50:28 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	assign_checks(t_type type, int (**checks)(char *))
{
	if (type == AMBIENT)
		ambient_checks(checks);
	else if (type == CAMERA)
		camera_checks(checks);
	else if (type == LIGHT)
		lights_checks(checks);
	else if (type == SPHERE)
		sphere_checks(checks);
	else if (type == PLANE)
		plane_checks(checks);
	else if (type == CYLINDER)
		cylinder_checks(checks);
}

/* Jumps to the next 'token' of the line read from the line
	first to end of 'token' and then skips all spaces
	returns NULL if there are no more 'tokens' */
static char	*next_value(char *ptr)
{
	ptr = ft_strchr(ptr, ' ');
	if (ptr == NULL)
		return (NULL);
	while (ft_isspace(*ptr))
		ptr++;
	return (ptr);
}

/* Checks validity of line read from file by looping through
	validation functions every value must be correct,
	and there must not be any extra values */
int	validate(char *line)
{
	int		(*checks[6])(char *);
	int		i;
	t_type	type;

	type = get_type(line);
	if (line == NULL || ft_isspace(*line) || *line == '\0' || type == NONE)
		return (FAILURE);
	assign_checks(type, checks);
	i = 0;
	while (checks[i] != NULL)
	{
		line = next_value(line);
		if (line == NULL || (checks[i])(line) == 0)
		{
			printf("%s: Failed at check: %d\n", line, i);
			return (FAILURE);
		}
		i++;
	}
	line = next_value(line);
	if (line != NULL && *line != '\0')
		return (FAILURE);
	return (SUCCESS);
}
