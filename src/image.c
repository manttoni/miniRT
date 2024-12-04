#include "../inc/minirt.h"

t_image	*init_image(t_data *data)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	image->img = mlx_new_image(data->mlx, data->x, data->y);
	image->img_data = mlx_get_data_addr(image->img, \
			&(image->bits_per_pixel), \
			&(image->size_line), \
			&(image->endian));
	image->focal_len = 1000;
	return (image);
}

void	free_image(void *mlx, t_image *image)
{
	mlx_destroy_image(mlx, image->img);
	free(image);
}

void	color_pixel(t_data *data, int pixel_color, int x, int y)
{
	int	pixel_index;
	t_image	*image;

	image = data->image;
	x += data->x / 2;
	y += data->y / 2;
	pixel_index = y * image->size_line + x * (image->bits_per_pixel / 8);
	*(int *)(image->img_data + pixel_index) = pixel_color;
}
