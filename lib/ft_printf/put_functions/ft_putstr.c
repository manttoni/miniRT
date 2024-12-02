/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:16:02 by amaula            #+#    #+#             */
/*   Updated: 2024/05/13 13:15:52 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putstr(char *s)
{
	int	ret;
	int	tmp;

	if (!s)
	{
		tmp = ft_putstr("(null)");
		if (tmp < 0)
			return (-1);
		return (tmp);
	}
	ret = 0;
	while (*s)
	{
		tmp = ft_putchar(*s);
		if (tmp < 0)
			return (-1);
		ret += tmp;
		s++;
	}
	return (ret);
}
