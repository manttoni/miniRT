#include <stdio.h>
#include "../includes/data.h"
#include "../includes/vector.h"
#include "../includes/object.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include "../includes/keyhandler.h"
#include "../includes/ray.h"

void print_objects(t_node *objects)
{
	t_object *o;
	while (objects)
	{
		o = (t_object *) objects->data;
		print_object(o);
		objects = objects->next;
	}
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
	if (argc == 2)
	{
		if (format_validation(argv[1]))
		{
			printf("Wrong type of file\n");
			return (1);
		}
		t_data	*data = init_data(argv[1]);
		if (data == NULL)
			return (1);
		print_objects(data->objects);
		printf("---------------\n");
		raycast(data);
		mlx_key_hook(data->mlx, &keypress, data);
		mlx_image_to_window(data->mlx, data->image , 0, 0);
		mlx_loop(data->mlx);
		mlx_terminate(data->mlx);
		free_data(data);
	}
	else
		printf("Too many arguments\n");
	return (0);
}
