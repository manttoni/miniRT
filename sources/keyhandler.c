
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
	// static t_object *selected;
	// static t_vector axis;

	data = (t_data *)param;
	if (mlx_data.action == MLX_PRESS)
	{
		if (mlx_data.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(data->mlx);
			return ;
		}
		// if (mlx_data.key == MLX_KEY_TAB)
		// {
		// 	selected = select_next_object(selected, data->objects);
		// 	print_object(selected);
		// }
		// if (mlx_data.key == MLX_KEY_X)
		// {
		// 	axis = vector(1, 0, 0);
		// 	printf("Move X\n");
		// }
		// if (mlx_data.key == MLX_KEY_Y)
		// {
		// 	axis = vector(0, 1, 0);
		// 	printf("Move Y\n");
		// }
		// if (mlx_data.key == MLX_KEY_Z)
		// {
		// 	axis = vector(0, 0, 1);
		// 	printf("Move Z\n");
		// }
		// if (mlx_data.key == MLX_KEY_KP_ADD)
		// {
		// 	selected->location = v_sum(selected->location, axis);
		// 	print_vector(selected->location);
		// }
		// if (mlx_data.key == MLX_KEY_KP_SUBTRACT)
		// {
		// 	selected->location = v_sub(selected->location, axis);
		// 	print_vector(selected->location);
		// }
		// if (mlx_data.key == MLX_KEY_ENTER)
		// 	redraw(data);
	}
}
