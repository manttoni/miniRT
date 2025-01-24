#include "../includes/minirt.h"

// void	free_image(void *mlx, t_image *image)
// {
// 	mlx_destroy_image(mlx, image->img);
// 	free(image);
// }

void	color_pixel(mlx_image_t *image, uint32_t pixel_color, int x, int y)
{
	int	pixel_index;

	// if (x < 0 || x >= X || y < 0 || y >= 0)
	// 	return ;
	pixel_index = y * X + x;
	((uint32_t *)(image->pixels))[pixel_index] = pixel_color;
}
