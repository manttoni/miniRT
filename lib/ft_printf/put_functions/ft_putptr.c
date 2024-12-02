/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:23:01 by amaula            #+#    #+#             */
/*   Updated: 2024/05/13 13:14:23 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putptr(void *p)
{
	int	ret;
	int	tmp;

	tmp = ft_putstr("0x");
	if (tmp < 0)
		return (-1);
	ret = tmp;
	tmp = ft_puthex((unsigned long) p);
	if (tmp < 0)
		return (-1);
	return (tmp + ret);
}
