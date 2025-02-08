#include "../includes/minirt.h"

/* Rotates camera to look at the cursor*/
void    left_click(t_data *data)
{
    t_object    *camera;
    t_vector    new_orientation;

    mlx_get_mouse_pos(data->mlx, &(data->mouse.x), &(data->mouse.y));
    camera = get_object(data->objects, CAMERA);
    new_orientation = get_ray(camera, data->mouse.x, data->mouse.y).direction;
    rotate_object(get_object(data->objects, CAMERA), new_orientation, data->objects);
    redraw(data);
}

/* Selects an object at the cursor*/
void    right_click(t_data *data)
{
    t_ray   ray;

    mlx_get_mouse_pos(data->mlx, &(data->mouse.x), &(data->mouse.y));
    ray = get_ray(get_object(data->objects, CAMERA), data->mouse.x, data->mouse.y);
    if (cast_ray(&ray, data->objects) == 1)
    {
        if (data->ui->selected != ray.object)
            select_object(ray.object, data->ui);
    }
}

/* mouse.left and mouse.right checks prevent the program from executing the functions every frame */
void	rt_mouse(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT) && !data->mouse.left)
	{
		data->mouse.left = 1;
		left_click(data);
	}
	else if (!mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
		data->mouse.left = 0;

	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_RIGHT) && !data->mouse.right)
	{
		data->mouse.right = 1;
		right_click(data);
	}
	else if (!mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_RIGHT))
		data->mouse.right = 0;
}
