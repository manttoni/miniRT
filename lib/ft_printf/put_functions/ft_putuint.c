/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:28:44 by amaula            #+#    #+#             */
/*   Updated: 2024/05/13 13:15:04 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putuint(unsigned int ui)
{
	int	ret;
	int	tmp;

	ret = 0;
	if (ui >= 10)
	{
		tmp = ft_putuint(ui / 10);
		if (tmp < 0)
			return (-1);
		ret += tmp;
	}
	tmp = ft_putchar(ui % 10 + '0');
	if (tmp < 0)
		return (-1);
	return (ret + tmp);
}
