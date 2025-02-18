/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:51:24 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 15:41:52 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * print_vector - Prints a 3D vector with its length.
 *
 * @v: The vector to be printed.
 *
 * This function prints the x, y, and z components of the vector,
 * along with its computed length using `v_len(v)`.
 */
void	print_vector(t_vector v)
{
	printf("x: %1.2f, y: %1.2f, z: %1.2f, len: %1.2f\n",
		v.x, v.y, v.z, v_len(v));
}

/**
 * print_color - Prints an RGB color in hex format with terminal coloring.
 *
 * @color: The color value in ARGB format (uint32_t).
 *
 * This function extracts the red, green, and blue components from
 * the 32-bit integer and prints the color with ANSI escape codes
 * to display it in the corresponding color in the terminal.
 */
void	print_color(uint32_t color)
{
	printf("\033[38;2;%d;%d;%dm%06X\033[0m\n",
		(color >> 24) & 0xFF, (color >> 16) & 0xFF,
		(color >> 8) & 0xFF, color);
}


/**
 * print_objects - Prints all objects in the scene.
 *
 * @data: Pointer to the scene data structure.
 *
 * This function prints the details of all objects in the scene,
 * including the camera, light, ambient light, and all other objects
 * stored in the object array.
 */
void	print_objects(t_data *data)
{
	size_t		i;
	t_object	o;

	i = 0;
	printf("-------------\n");
	data->camera->print_object(data->camera);
	printf("-------------\n");
	data->light->obj->print_object(data->light->obj);
	printf("-------------\n");
	data->ambient->obj->print_object(data->ambient->obj);
	while (i < data->objects->objects)
	{
		o = data->objects->arr[i];
		printf("-------------\n");
		printf("Index: %zu\n", i);
		o.print_object(&o);
		i++;
	}
	printf("-------------\n");
}

/**
 * print_help - Displays a help menu for user controls.
 *
 * This function prints instructions for interacting with the ray tracing
 * program, including movement, object selection, and scene manipulation.
 */
void	print_help(void)
{
	printf("--------------\n");
	printf("HOME: print objects\n");
	printf("H: this menu\n");
	printf("Select object: right click, number keys and C L A\n");
	printf("Movement keys (numpad):\n");
	printf("L/R: 4 & 6\nUP/DOWN: 8 & 2\nFORWARD/BACK: 9 & 1\n");
	printf("Left click rotates camera\n");
	printf("Arrow keys rotate selected object\n");
	printf("Numpad + and - change brightness, fov or diameter\n");
	printf("Page up and down change cylinder height\n");
}
