
#include "../includes/minirt.h"

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

void	free_data(t_data *data)
{
	if (data == NULL)
		return ;
	free_list(data->objects);
	free(data);
}
