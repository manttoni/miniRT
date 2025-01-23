
#include "../includes/minirt.h"

void print_objects(t_node *objects)
{
	t_object *o;
	while (objects)
	{
		o = (t_object *) objects->data;
		if (o->type == CAMERA)
		{
			printf("---------------\n");
			printf("Camera:\nLocation: ");
			print_vector(o->location);
			printf("Orientation: ");
			print_vector(o->orientation);
			printf("FOV: %d\n", o->fov);
		}
		else if (o->type == SPHERE)
		{
			printf("---------------\n");
			printf("Sphere:\nLocation: ");
			print_vector(o->location);
			printf("Diameter: %f\n", o->diameter);
			printf("Color: %x\n", o->color);
		}
		else if (o->type == PLANE)
		{
			printf("---------------\n");
			printf("Plane:\nLocation: ");
			print_vector(o->location);
			printf("Normal: ");
			print_vector(o->orientation);
			printf("Color: %x\n", o->color);
		}
		objects = objects->next;
	}
}

int main(void)
{
	t_data	*data = init_data(1000, 750, "test.rt");
	if (data == NULL)
	{
		printf("data initialization failed\n");
		free_data(data);
		return (1);
	}
	get_camera(data->objects)->view_distance = 1000;
	print_objects(data->objects);
	printf("---------------\n");
	raycast(data);
	//mlx_key_hook(data->win, &handle_key, data);
	mlx_key_hook(data->mlx, &keypress, data);
	//mlx_hook(data->win, 17, 0, handle_close, data);
	mlx_image_to_window(data->mlx, data->image->img , 0, 0);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}
