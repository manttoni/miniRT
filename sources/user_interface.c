/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:49:44 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 15:50:25 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * select_object - Selects an object and updates the current selection.
 *
 * @object: The object to be selected.
 * @data: The main data structure containing the scene.
 *
 * This function updates the `selected` pointer in the `data` structure
 * to point to the specified object. It then prints the details of
 * the selected object using its `print_object` function.
 */
void	select_object(t_object *object, t_data *data)
{
	data->selected = object;
	printf("Object selected: \n");
	object->print_object(object);
}
