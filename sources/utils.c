/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:53:48 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 11:53:49 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

char	*trim_newline(char *str)
{
	char	*trimmed;
	size_t	len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	if (str[len - 1] == '\n')
		trimmed = ft_substr(str, 0, len - 1);
	else
		return (str);
	free(str);
	return (trimmed);
}
