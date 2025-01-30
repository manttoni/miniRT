
#include "../includes/minirt.h"

/**
 * mlx_and_image - Initializes MLX42 and creates an image.
 * @data: Pointer to the t_data structure.
 *
 * This function:
 * - Initializes MLX42 with a window of size (X, Y) named "miniRT".
 * - Creates an MLX42 image with the same dimensions.
 *
 * If initialization fails, it calls `error_msg(data)` and returns 1.
 *
 * Return:
 * - 0 on success.
 * - 1 if MLX initialization or image creation fails.
 */
int	mlx_and_image(t_data *data)
{
	data->mlx = mlx_init(X, Y, "miniRT", true);
	if (data->mlx == NULL)
	{
		error_msg(data);
		return (1);
	}
	data->image = mlx_new_image(data->mlx, X, Y);
	if (data->image == NULL)
	{
		error_msg(data);
		return (1);
	}
	return (0);
}

/**
 * init_data - Allocates and initializes the main data structure.
 * @file: The filename containing the scene description (.rt format).
 *
 * This function:
 * - Allocates memory for `t_data` structure.
 * - Initializes it using `ft_bzero` to clear the memory.
 * - Parses objects from the given file using `read_objects`.
 * - Calls `mlx_and_image` to set up MLX42 and the rendering image.
 *
 * If any initialization step fails, it:
 * - Prints an error message.
 * - Frees allocated memory (if applicable).
 * - Returns NULL to indicate failure.
 *
 * Return:
 * - Pointer to `t_data` on success.
 * - NULL if an error occurs.
 */
t_data	*init_data(char *file)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		error_msg(data);
		return (NULL);
	}
	ft_bzero(data, sizeof(t_data));
	data->objects = read_objects(file);
	if (!data->objects)
	{
		error_msg(data);
		free(data);
		return (NULL);
	}
	if (mlx_and_image(data))
		return (NULL);
	return (data);
}

/**
 * free_data - Frees memory allocated for the main data structure.
 * @data: Pointer to the t_data structure.
 *
 * This function:
 * - Frees the list of objects using `free_list`.
 * - Frees the `data` structure itself.
 *
 * If `data` is NULL, the function does nothing.
 */
void	free_data(t_data *data)
{
	if (data == NULL)
		return ;
	free_list(data->objects);
	free(data);
}
