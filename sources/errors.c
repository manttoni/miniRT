#include "../includes/minirt.h"

int	failure(char *message)
{
	printf("Error\n\t%s\n", message);
	return (FAILURE);
}

void	error_msg(t_data *data)
{
	if (!data)
	{
		failure("Data structure failed");
		return ;
	}
	if (!data->objects)
	{
		failure("Failed create data objects");
		return ;
	}
	if (!data->mlx)
		failure("MLX failed to initialize");
	if (!data->image)
		failure("No image");
	return ;
}
