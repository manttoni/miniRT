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

static int	format_validation(int argc, char **argv)
{
	int		len;
	char	*str;

	if (argc != 2)
		return (failure("Wrong amount of arguments"));
	str = argv[1];
	len = ft_strlen(str);
	if (ft_strncmp(&str[len - 3], ".rt", 3) != 0)
		return (failure("Wrong filetype"));
	return (0);
}

int main(int argc, char **argv)
{
	if (format_validation(argc, argv) == 1)
		return (1);
	t_data	*data = init_data(argv[1]);
	if (data == NULL)
		return (failure("data initialization failed"));
	print_objects(data->objects);
	raycast(data);
	mlx_key_hook(data->mlx, &keypress, data);
	mlx_image_to_window(data->mlx, data->image , 0, 0);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	free_data(data);
	return (0);
}
