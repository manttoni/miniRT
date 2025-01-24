
#include "../includes/minirt.h"

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (ft_strcmp(ft_strrchr(argv[1], '.'), ".rt") != 0
		|| ft_countchar(argv[1], '.') != 1)
		{
			printf("wrong type of file\n");
			return (1);
		}
		t_data	*data = init_data(argv[1]);
		if (data == NULL)
		{
			printf("Data initialization failed\n");
			free_data(data);
			return (1);
		}
		get_camera(data->objects)->view_distance = 1000;
		raycast(data);
		mlx_key_hook(data->mlx, &keypress, data);
		mlx_image_to_window(data->mlx, data->image->img , 0, 0);
		mlx_loop(data->mlx);
		mlx_terminate(data->mlx);
	}
	else
		printf("Too many arguments\n");
	return (0);
}
