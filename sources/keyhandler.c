
#include "../includes/minirt.h"

/**
 * handle_close - Cleans up memory and exits the program when the window closes.
 * @param: A pointer to the `t_data` structure (passed as `param`).
 *
 * This function:
 * - Calls `free_data(param)` to release all allocated memory.
 * - Exits the program with `exit(0)`.
 *
 * This function is used as a **callback** when the window is closed.
 *
 * Return: Always exits the program (no return value).
 */
int	handle_close(void *param)
{
	free_data(param);
	exit(0);
}

/**
 * select_next_object - Selects the next object in the linked list.
 * @selected: The currently selected object.
 * @objects: The head of the object list.
 *
 * This function:
 * - If `selected` is `NULL`, it returns the first object in `objects`.
 * - If `selected` is found in the list:
 *   - Returns the next object if available.
 *   - Otherwise, wraps around and returns the first object.
 * - If `selected` is not found in `objects`, it returns `NULL`.
 *
 * This function allows cycling through all objects using the `TAB` key.
 *
 * Return:
 * - Pointer to the next selected object.
 * - NULL if the list is empty.
 */
static t_object *select_next_object(t_object *selected, t_object *objects)
{
	t_object	*current;

	if (selected == NULL)
		return (objects);
	current = objects;
	while (current)
	{
		if (current == selected)
		{
			if (current->next == NULL)
				return (objects);
			else
				return (current->next);
		}
		current = current->next;
	}
	return (NULL);
}

/**
 * redraw - Rerenders the scene after object transformations.
 * @data: Pointer to the `t_data` structure.
 *
 * This function:
 * - Calls `raycast(data)` to recalculate the image.
 * - Displays the updated image using `mlx_image_to_window`.
 *
 * It is triggered when the `ENTER` key is pressed.
 */
static void redraw(t_data *data)
{
	raycast(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}

/**
 * keypress - Handles keyboard input for object selection and transformations.
 * @mlx_data: The MLX42 key event structure.
 * @param: A pointer to the `t_data` structure.
 *
 * This function:
 * - Closes the window when `ESC` is pressed.
 * - Selects the next object when `TAB` is pressed.
 * - Changes the movement axis when `X`, `Y`, or `Z` is pressed.
 * - Moves the selected object along the chosen axis using `KP_ADD` and `KP_SUBTRACT`.
 * - Redraws the scene when `ENTER` is pressed.
 */
void	keypress(mlx_key_data_t mlx_data, void *param)
{
	t_data	*data;
	static t_object *selected;
	static t_vector axis;

	data = (t_data *)param;
	if (mlx_data.action == MLX_PRESS)
	{
		if (mlx_data.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(data->mlx);
			return ;
		}
		if (mlx_data.key == MLX_KEY_TAB)
		{
			selected = select_next_object(selected, data->objects);
			print_object(selected);
		}
		if (mlx_data.key == MLX_KEY_X)
		{
			axis = vector(1, 0, 0);
			printf("Move X\n");
		}
		if (mlx_data.key == MLX_KEY_Y)
		{
			axis = vector(0, 1, 0);
			printf("Move Y\n");
		}
		if (mlx_data.key == MLX_KEY_Z)
		{
			axis = vector(0, 0, 1);
			printf("Move Z\n");
		}
		if (mlx_data.key == MLX_KEY_KP_ADD)
		{
			selected->location = v_sum(selected->location, axis);
			print_vector(selected->location);
		}
		if (mlx_data.key == MLX_KEY_KP_SUBTRACT)
		{
			selected->location = v_sub(selected->location, axis);
			print_vector(selected->location);
		}
		if (mlx_data.key == MLX_KEY_ENTER)
			redraw(data);
	}
}
