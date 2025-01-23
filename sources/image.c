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
	// t_image	*image;

	// image = data->image;

	pixel_index = y * X + x;
	//if (pixel_index >= 800000)
      //  return;
	((uint32_t *)(image->img->pixels))[pixel_index] = (uint32_t)pixel_color;
}
