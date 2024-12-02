/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:25:48 by amaula            #+#    #+#             */
/*   Updated: 2024/05/12 14:33:42 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putdec(int d)
{
	int		ret;
	int		tmp;
	long	ld;

	ld = (long) d;
	ret = 0;
	if (ld < 0)
	{
		tmp = ft_putchar('-');
		if (tmp < 0)
			return (-1);
		ret += tmp;
		ld = -ld;
	}
	if (ld >= 10)
	{
		tmp = ft_putdec(ld / 10);
		if (tmp < 0)
			return (-1);
		ret += tmp;
	}
	tmp = ft_putchar(ld % 10 + '0');
	if (tmp < 0)
		return (-1);
	return (ret + tmp);
}
