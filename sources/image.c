#include "../includes/minirt.h"

t_image	*init_image(t_data *data)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	image->img = mlx_new_image(data->mlx, X, Y);
	image->img_data = (char *)image->img->pixels;
	image->bits_per_pixel = sizeof(uint32_t *);
	image->size_line = X;
	image->endian = 0;
	image->focal_len = 1000;
	return (image);
}

// void	free_image(void *mlx, t_image *image)
// {
// 	mlx_destroy_image(mlx, image->img);
// 	free(image);
// }

void	color_pixel(t_image *image, int pixel_color, int x, int y)
{
	int	pixel_index;

	// if (x < 0 || x >= X || y < 0 || y >= 0)
	// 	return ;
	pixel_index = y * X + x;
	((uint32_t *)(image->img->pixels))[pixel_index] = (uint32_t)pixel_color;
}
