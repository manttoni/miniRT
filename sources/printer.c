#include "../includes/minirt.h"

void	print_vector(t_vector v)
{
	printf("x: %1.2f, y: %1.2f, z: %1.2f, len: %1.2f\n",
		v.x, v.y, v.z, v_len(v));
}

void	print_color(uint32_t color)
{
		printf("\033[38;2;%d;%d;%dm%06X\033[0m\n",
		(color >> 24) & 0xFF, (color >> 16) & 0xFF,
		(color >> 8) & 0xFF, color);
}

void	print_objects(t_data *data)
{
	size_t		i;
	t_object	o;

	i = 0;
	printf("-------------\n");
	data->camera->print_object(data->camera);
	printf("-------------\n");
	data->light->light->print_object(data->light->light);
	printf("-------------\n");
	data->ambient->ambient->print_object(data->ambient->ambient);
	while (i < data->objects->objects)
	{
		o = data->objects->arr[i];
		printf("-------------\n");
		printf("Index: %zu\n", i);
		o.print_object(&o);
		i++;
	}
	printf("-------------\n");
}

void	print_help(void)
{
	printf("--------------\n");
	printf("HOME: print objects\n");
	printf("COMMA: this menu\n");
	printf("Select object: right click, number keys and C L A\n");
	printf("Movement keys (numpad):\n");
	printf("L/R: 4 & 6\nUP/DOWN: 8 & 2\nFORWARD/BACK: 9 & 1\n");
	printf("Left click rotates camera\n");
	printf("Arrow keys rotate selected object\n");
	printf("Numpad + and - change brightness, fov or diameter\n");
	printf("Page up and down change cylinder height\n");
}