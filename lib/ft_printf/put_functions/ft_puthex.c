/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:33:31 by amaula            #+#    #+#             */
/*   Updated: 2024/05/13 13:12:57 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_puthex(unsigned long h)
{
	char	digit;
	int		ret;
	int		tmp;

	ret = 0;
	if (h >= 16)
	{
		tmp = ft_puthex(h / 16);
		if (tmp < 0)
			return (-1);
		ret += tmp;
	}
	digit = h % 16;
	if (digit >= 10)
		digit += 'a' - 10;
	else
		digit += '0';
	tmp = ft_putchar(digit);
	if (tmp < 0)
		return (-1);
	return (ret + tmp);
}
