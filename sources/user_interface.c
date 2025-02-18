/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:49:44 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 11:49:48 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/* data->ui holds the selected object which reacts to movement keys */
void	select_object(t_object *object, t_data *data)
{
	data->selected = object;
	printf("Object selected: \n");
	object->print_object(object);
}
