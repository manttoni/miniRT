#include "../includes/minirt.h"

void print_objects(t_objarr *objarr)
{
	size_t	i;

	i = 0;
	while (i < objarr->objects)
	{
		print_object(objarr->arr[i]);
		i++;
	}
	printf("---------------\n");
}

static void	the_image(t_data *data)
{
	mlx_key_hook(data->mlx, &keypress, data);
	mlx_image_to_window(data->mlx, data->image , 0, 0);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	mlx_loop_hook(data->mlx, &rt_mouse, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}

static int	format_validation(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strncmp(&str[len - 3], ".rt", 3) != 0)
		return (failure("Wrong file type"));
	return (0);
}

int main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
	{
		printf("Error\n\tWrong amount of arguments!\n");
		return (1);
	}
	if (format_validation(argv[1]))
		return (1);
	data = init_data(argv[1]);
	if (data == NULL)
		return (1);
		// return (failure("Data initialization failed"));
	print_objects(data->objects);
	raycast(data);
	the_image(data);
	free_data(data);
	return (0);
}
