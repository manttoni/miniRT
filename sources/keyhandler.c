/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:50:16 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 15:12:30 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * select_object_by_index - Selects an object based on key input.
 *
 * @mlx_data: The key event data.
 * @data: Pointer to the main program data structure.
 *
 * If 'C', 'L', or 'A' is pressed, selects the camera, light, or ambient
 * light respectively. If a number key ('0' to '9') is pressed, selects
 * the corresponding object in the object array, if it exists.
 */
static void	select_object_by_index(mlx_key_data_t mlx_data, t_data *data)
{
	if (mlx_data.key == MLX_KEY_C)
		select_object(data->camera, data);
	if (mlx_data.key == MLX_KEY_L)
		select_object(data->light->obj, data);
	if (mlx_data.key == MLX_KEY_A)
		select_object(data->ambient->obj, data);
	if (mlx_data.key >= MLX_KEY_0 && mlx_data.key <= MLX_KEY_9)
	{
		if (mlx_data.key - MLX_KEY_0 < data->objects->objects)
			select_object(&data->objects->arr[mlx_data.key - MLX_KEY_0], data);
	}
}

/**
 * translate - Moves the selected object based on key input.
 *
 * @mlx_data: The key event data.
 * @selected: Pointer to the currently selected object.
 * @data: Pointer to the main program data structure.
 *
 * Moves the object in the direction of the camera's orientation
 * or along the image plane's basis vectors. The movement keys
 * correspond to numpad keys (8, 2, 4, 6, 9, 1).
 *
 * Returns:
 * - SUCCESS if the translation occurs.
 * - FAILURE if no valid movement key is pressed.
 */
static int	translate(mlx_key_data_t mlx_data, t_object *selected, t_data *data)
{
	t_vector	delta;
	t_object	*camera;

	if (selected == NULL)
		return (failure("No object selected"));
	camera = data->camera;
	if (mlx_data.key == MLX_KEY_KP_9)
		delta = camera->orientation;
	else if (mlx_data.key == MLX_KEY_KP_1)
		delta = v_mul(-1, camera->orientation);
	else if (mlx_data.key == MLX_KEY_KP_2)
		delta = data->info.v;
	else if (mlx_data.key == MLX_KEY_KP_8)
		delta = v_mul(-1, data->info.v);
	else if (mlx_data.key == MLX_KEY_KP_6)
		delta = data->info.u;
	else if (mlx_data.key == MLX_KEY_KP_4)
		delta = v_mul(-1, data->info.u);
	else
		return (FAILURE);
	translate_object(selected, delta);
	return (SUCCESS);
}

/**
 * change_value - Modifies an object's properties based on key input.
 *
 * @mlx_data: The key event data.
 * @selected: Pointer to the currently selected object.
 *
 * Adjusts object properties:
 * - Resizes spheres and cylinders.
 * - Adjusts brightness for lights and ambient light.
 * - Changes the FOV for the camera.
 *
 * Returns:
 * - SUCCESS if a property is modified.
 * - FAILURE if no valid modification is possible.
 */
static int	change_value(mlx_key_data_t mlx_data, t_object *selected)
{
	if (selected->type == SPHERE || selected->type == CYLINDER)
		return (resize_object(mlx_data, selected));
	if (selected->type == LIGHT || selected->type == AMBIENT)
		return (adjust_brightness(mlx_data, selected));
	if (selected->type == CAMERA)
		return (change_fov(mlx_data, selected));
	return (FAILURE);
}

/**
 * rotate - Rotates the selected object's orientation.
 *
 * @mlx_data: The key event data.
 * @selected: Pointer to the currently selected object.
 * @data: Pointer to the main program data structure.
 *
 * Rotates the object around the image plane's basis vectors:
 * - Left/Right arrows rotate around the vertical axis.
 * - Up/Down arrows rotate around the horizontal axis.
 *
 * Returns:
 * - SUCCESS if rotation occurs.
 * - FAILURE if no valid rotation key is pressed.
 */
static int	rotate(mlx_key_data_t mlx_data, t_object *selected, t_data *data)
{
	float		d;

	d = 0.1;
	if (mlx_data.key == MLX_KEY_LEFT)
		rotate_vector(&(selected->orientation), data->info.v, -d);
	else if (mlx_data.key == MLX_KEY_RIGHT)
		rotate_vector(&(selected->orientation), data->info.v, d);
	else if (mlx_data.key == MLX_KEY_UP)
		rotate_vector(&(selected->orientation), data->info.u, d);
	else if (mlx_data.key == MLX_KEY_DOWN)
		rotate_vector(&(selected->orientation), data->info.u, -d);
	else
		return (FAILURE);
	return (SUCCESS);
}

/**
 * keypress - Handles key press events and updates the scene.
 *
 * @mlx_data: The key event data.
 * @param: Pointer to the main program data structure.
 *
 * Supports multiple actions:
 * - Escape: Closes the program.
 * - Home: Prints all objects.
 * - H: Prints help instructions.
 * - R: Resets the scene.
 * - Arrow keys & numpad: Translates or rotates the selected object.
 * - Number keys (0-9): Selects an object by index.
 *
 * If any action modifies the scene, it triggers a redraw.
 */
void	keypress(mlx_key_data_t mlx_data, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_data.action == MLX_PRESS)
	{
		if (mlx_data.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(data->mlx);
			return ;
		}
		if (mlx_data.key == MLX_KEY_HOME)
			print_objects(data);
		if (mlx_data.key == MLX_KEY_H)
			print_help();
		if (mlx_data.key == MLX_KEY_R)
			reset_scene(data);
		if (translate(mlx_data, data->selected, data) == SUCCESS)
			redraw(data);
		if (rotate(mlx_data, data->selected, data) == SUCCESS)
			redraw(data);
		if (change_value(mlx_data, data->selected) == SUCCESS)
			redraw(data);
		select_object_by_index(mlx_data, data);
	}
}
