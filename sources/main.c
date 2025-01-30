#include "../includes/minirt.h"

void print_objects(t_objarr *objects)
{
	int	i;

	i = 0;
	while (objects->arr[i] != NULL)
	{
		print_object(objects->arr[i]);
		i++;
	}
	printf("---------------\n");
}

static int	format_validation(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strncmp(&str[len - 3], ".rt", 3) != 0)
		return (1);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Wrong amount of arguments!\n");
		return (1);
	}
	if (format_validation(argv[1]))
	{
		printf("Wrong type of file\n");
		return (1);
	}
	t_data	*data = init_data(argv[1]);
	if (data == NULL)
		return (1);
	print_objects(data->objects);
	raycast(data);
	mlx_key_hook(data->mlx, &keypress, data);
	mlx_image_to_window(data->mlx, data->image , 0, 0);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	free_data(data);
	return (0);
}
