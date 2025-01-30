#include "../includes/minirt.h"

/**
 * min - Returns the smaller of two integers.
 * @a: First integer.
 * @b: Second integer.
 *
 * Return:
 * - The **minimum** value between `a` and `b`.
 */
int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

/**
 * max - Returns the larger of two integers.
 * @a: First integer.
 * @b: Second integer.
 *
 * Return:
 * - The **maximum** value between `a` and `b`.
 */
int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

/**
 * trim - Removes all occurrences of a character from the start and end of a string.
 * @str: The input string.
 * @c: The character to remove.
 *
 * This function:
 * - Moves `start` forward to skip leading `c` characters.
 * - Moves `end` backward to skip trailing `c` characters.
 * - Allocates memory for a new trimmed string.
 * - Copies the trimmed content into the new string.
 * - Frees the original string.
 *
 * Return:
 * - A **newly allocated string** without leading/trailing `c`.
 * - `NULL` if allocation fails.
 */
char	*trim(char *str, char c)
{
	char	*start;
	char	*end;
	char	*trimmed;
	int		i;

	if (str == NULL)
		return (NULL);
	start = str;
	while (*start == c)
		start++;
	end = str + ft_strlen(str);
	while (*end == c)
		end--;
	trimmed = malloc(end - start);
	if (trimmed == NULL)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (i < (end - start) - 1)
	{
		trimmed[i] = start[i];
		i++;
	}
	free(str);
	trimmed[i] = '\0';
	return (trimmed);
}

/**
 * error_msg - Displays error messages if `t_data` components are NULL.
 * @data: Pointer to the `t_data` structure.
 *
 * This function:
 * - Prints `"Data structure failed"` if `data` is NULL.
 * - Prints `"Failed create data objects"` if `data->objects` is NULL.
 * - Prints `"MLX failed to initialize"` if `data->mlx` is NULL.
 * - Prints `"No image"` if `data->image` is NULL.
 *
 */
void	error_msg(t_data *data)
{
	if (!data)
	{
		printf("Data structure failed\n");
		return ;
	}
	if (!data->objects)
	{
		printf("Failed create data objects\n");
		return ;
	}
	if (!data->mlx)
		printf("MLX failed to initialize\n");
	if (!data->image)
		printf("No image\n");
	return ;
}
