/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 12:41:59 by amaula            #+#    #+#             */
/*   Updated: 2025/01/24 16:50:57 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/libft.h"

char	*gnl_join(char *dst, char *src, size_t len)
{
	char			*ret;
	char			*ptr;
	size_t			bytes;
	unsigned int	i;

	if (!*src)
		return (dst);
	if (dst == NULL || src == NULL)
		return (NULL);
	bytes = ft_strlen(dst) + len + 1;
	ret = malloc(bytes);
	if (ret == NULL)
	{
		free(dst);
		return (NULL);
	}
	i = 0;
	ptr = dst;
	while (*dst)
		ret[i++] = *dst++;
	while (i < bytes - 1)
		ret[i++] = *src++;
	free(ptr);
	ret[i] = '\0';
	return (ret);
}

void	gnl_copy(char *dst, char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}
