/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:53:48 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 16:04:32 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * min - Returns the minimum of two integers.
 *
 * @a: The first integer.
 * @b: The second integer.
 *
 * Return: The smaller of the two integers.
 */
int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

/**
 * max - Returns the maximum of two integers.
 *
 * @a: The first integer.
 * @b: The second integer.
 *
 * Return: The larger of the two integers.
 */
int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

/**
 * trim_newline - Removes the newline character at the end of a string.
 *
 * @str: The string to be processed.
 *
 * Note: The function allocates memory for a new string if a newline is found
 *       and frees the original string.
 *
 * Return: A new string without the trailing newline.
 *         If no newline is present, returns the original string.
 *         Returns NULL if the input string is NULL.
 */
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
